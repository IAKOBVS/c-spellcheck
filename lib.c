/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 James Tirta Halim <tirtajames45 at gmail dot com>
 * This file is part of c-spellcheck.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>

#define JTRIE_ASCII_SIZE       (('Z' - 'A') + ('z' - 'a') + ('9' - '0') + '1')
#define JTRIE_ASCII_IDX_GET(c) get_compressed_idx((unsigned char)c)

static int
get_compressed_idx(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c - 'A';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + ('Z' - 'A');
	if (c >= '0' && c <= '9')
		return c - '0' + ('Z' - 'A') + ('z' - 'a');
	/* if (c == '_') */
	return ('Z' - 'A') + ('z' - 'a') + ('9' - '0');
}

#include "trie.h"

typedef enum fn_mode_ty {
	FN_DECLARED,
	FN_CALLED
} fn_mode_ty;

typedef struct llist_ty {
	char *value;
	struct llist_ty *next;
} llist_ty;

typedef struct fnlist_ty {
	char *fn_name;
	int fn_id;
	llist_ty *fn_args;
	struct fnlist_ty *next;
} fnlist_ty;

void
fn_args_print(llist_ty *fn_args)
{
	if (fn_args->value == NULL)
		return;
	for (llist_ty *curr = fn_args; curr->next; curr = curr->next) {
		printf("%s", curr->value);
		if (curr->next->next)
			putchar(',');
	}
}

int
fn_args_count(llist_ty *fn_args)
{
	int i = 0;
	if (fn_args->value == NULL)
		return i;
	for (llist_ty *curr = fn_args; curr->next; curr = curr->next)
		++i;
	return i;
}

int
xiswhite(int c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

static void
remove_literal_strings(char *s)
{
	char *dst, *src;
	dst = src = s;
	for (;;) {
		switch (*src) {
		default:
			*dst++ = *src++;
			break;
		case '\0':
			goto at_nul;
		case '\\':
			*dst++ = *src++;
			if (*src == '\"')
				*dst++ = *src++;
			break;
		case '#':
			for (; *src && *src != '\n'; ++src)
				;
			if (*src == '\n')
				++src;
			break;
		case '"':
			++src;
			for (;;) {
				switch (*src) {
				default:
					++src;
					break;
				case '\0':
					fprintf(stderr, "Unmatched quotes.\n");
					exit(EXIT_FAILURE);
				case '\\':
					++src;
					if (*src == '\"')
						++src;
					break;
				case '"':
					++src;
					*dst++ = '"';
					*dst++ = '"';
					goto close_quote;
				}
			}
close_quote:;
		}
	}
at_nul:
	*dst = '\0';
}

static void *
xmemrchr(const void *s, int c, size_t n)
{
	const unsigned char *p = (const unsigned char *)s + n;
	while (n--)
		if (*--p == (unsigned char)c)
			return (void *)p;
	return NULL;
}

static void *
xmalloc(size_t n)
{
	void *p = malloc(n);
	assert(p);
	return p;
}

static void *
xrealloc(void *p, size_t n)
{
	p = realloc(p, n);
	assert(p);
	return p;
}

static void *
xcalloc(size_t n)
{
	void *p = calloc(1, n);
	assert(p);
	return p;
}

static char *
xmemdupz(const char *s, size_t n)
{
	char *p = xmalloc(n + 1);
	memcpy(p, s, n);
	*(p + n) = '\0';
	return p;
}

static char *
xstrdup(const char *s)
{
	return xmemdupz(s, strlen(s));
}

char *
file_alloc(const char *fname)
{
	FILE *fp = fopen(fname, "r");
	assert(fp);
	struct stat st;
	assert(!stat(fname, &st));
	char *p = xmalloc((size_t)(st.st_size + 1));
	assert(fread(p, 1, (size_t)st.st_size, fp) == (size_t)st.st_size);
	assert(!fclose(fp));
	p[st.st_size] = '\0';
	remove_literal_strings(p);
	return p;
}

void
file_free(char *s)
{
	free(s);
}

static int
starts_with(const char *s, const char *with)
{
	return !strncmp(s, with, strlen(with));
}

static int
is_fn_char(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

#define llist_next(node) node = (node)->next

llist_ty *
llist_alloc()
{
	return xcalloc(sizeof(llist_ty));
}

llist_ty *
llist_dup(llist_ty *node)
{
	llist_ty *ret_head = llist_alloc();
	llist_ty *ret_node = ret_head;
	for (; node->next; llist_next(node), llist_next(ret_node)) {
		ret_node->value = xstrdup(node->value);
		ret_node->next = llist_alloc();
	}
	return ret_head;
}

void
llist_node_free(llist_ty *node)
{
	free(node->value);
	free(node);
}

void
llist_free(llist_ty *node)
{
	if (node) {
		llist_free(node->next);
		llist_node_free(node);
	}
}

void
llist_insert_head(llist_ty **head, char *value)
{
	llist_ty *old_head = *head;
	*head = xmalloc(sizeof(llist_ty));
	(*head)->value = value;
	(*head)->next = old_head;
}

void
llist_insert_tail(llist_ty **tail, char *value)
{
	(*tail)->value = value;
	(*tail)->next = llist_alloc();
	llist_next(*tail);
}

void
llist_delete_curr(llist_ty **head, llist_ty *node, llist_ty *prev)
{
	if (prev)
		prev->next = node->next;
	else
		*head = node->next;
	llist_node_free(node);
}

void
llist_delete(llist_ty **head, llist_ty *target)
{
	llist_ty *node = *head, *prev = NULL;
	for (; node != target; llist_next(node))
		prev = node;
	llist_delete_curr(head, node, prev);
}

#define fnlist_next(node) llist_next(node)

fnlist_ty *
fnlist_alloc()
{
	return xcalloc(sizeof(fnlist_ty));
}

void
fnlist_node_free(fnlist_ty *node)
{
	free(node->fn_name);
	llist_free(node->fn_args);
	free(node);
}

void
fnlist_free(fnlist_ty *node)
{
	if (node) {
		fnlist_free(node->next);
		fnlist_node_free(node);
	}
}

void
fnlist_insert_head(fnlist_ty **head, char *fn_name, llist_ty *fn_args, int fn_id)
{
	fnlist_ty *old_head = *head;
	*head = xmalloc(sizeof(fnlist_ty));
	(*head)->fn_name = fn_name;
	(*head)->fn_args = fn_args;
	(*head)->next = old_head;
	(*head)->fn_id = fn_id;
}

void
fnlist_insert_tail(fnlist_ty **tail, char *fn_name, llist_ty *fn_args, int fn_id)
{
	(*tail)->fn_name = fn_name;
	(*tail)->fn_args = fn_args;
	(*tail)->fn_id = fn_id;
	(*tail)->next = fnlist_alloc();
	fnlist_next(*tail);
}

void
fnlist_delete_curr(fnlist_ty **head, fnlist_ty *node, fnlist_ty *prev)
{
	if (prev)
		prev->next = node->next;
	else
		*head = node->next;
	fnlist_node_free(node);
}

void
fnlist_delete(fnlist_ty **head, fnlist_ty *target)
{
	fnlist_ty *node = *head, *prev = NULL;
	for (; node != target; fnlist_next(node))
		prev = node;
	fnlist_delete_curr(head, node, prev);
}

static char *
fn_start(const char *start, const char *paren, const char **fn_end)
{
	const char *p = paren;
	while (--p >= start && xiswhite(*p)) {}
	*fn_end = p + 1;
	for (; p >= start && is_fn_char(*p); --p) {}
	++p;
	if (!is_fn_char(*p)
	    || *p == '_'
	    || (*p >= '0' && *p <= '9')
	    || starts_with(p, "if")
	    || starts_with(p, "for")
	    || starts_with(p, "while")
	    || starts_with(p, "return")
	    || starts_with(p, "switch")
	    || starts_with(p, "sizeof"))
		return NULL;
	return (char *)p;
}

/* TODO: have a more robust way of checking whether a function is declared or called.
 *       handle function pointers. */

fn_mode_ty
fn_get_type(const char *s, const char *end)
{
	const char *line = xmemrchr(s, '\n', (size_t)(end - s));
	line = (line != NULL) ? line + 1 : s;
	return (*line == '\t' || *line == ' ') ? FN_CALLED : FN_DECLARED;
}

char *
paren_end(const char *paren_s, const char *paren_e)
{
	const char *p = paren_s;
	if (*p == '(') {
		int end_paren = 1;
		while (++p <= paren_e) {
			if (*p == ')')
				--end_paren;
			else if (*p == '(')
				++end_paren;
			else
				continue;
			if (end_paren == 0)
				break;
		}
		if (end_paren)
			return NULL;
	}
	return (char *)p;
}

llist_ty *
fn_args_get(const char *paren_s, const char *paren_e)
{
	const char *p = paren_s;
	const char *arg_s = p + 1;
	const char *arg_e;
	llist_ty *arg_head = llist_alloc();
	llist_ty *arg_node = arg_head;
	for (; ++p <= paren_e; ) {
		switch (*p) {
		case '\0':
paren_error:
			fprintf(stderr, "Unmatched parenthesis.\n");
			exit(EXIT_FAILURE);
			goto ret;
			break;
		case '(':
			p = paren_end(p, paren_e);
			assert(p);
			if (p == NULL)
				goto paren_error;
			++p;
		case ',':
			for (; xiswhite(*arg_s); ++arg_s)
				;
			arg_e = p;
			if (arg_s < arg_e && xiswhite(*(arg_e - 1))) {
				--arg_e;
				for (; arg_s < arg_e && xiswhite(*arg_e); --arg_e)
					;
				++arg_e;
			}
			llist_insert_tail(&arg_node, xmemdupz(arg_s, (size_t)(arg_e - arg_s)));
			arg_s = p + 1;
			break;
		}
	}
ret:
	return arg_head;
}

int
fn_get(const char *s, const char **next, fn_mode_ty *fn_mode, fnlist_ty *node_dst, const char *file)
{
	const char *fn, *fn_end, *paren, *p;
	for (p = s;; p = paren + 1) {
		paren = strchr(p, '(');
		if (!paren)
			break;
		fn = fn_start(s, paren, &fn_end);
		if (fn) {
			*fn_mode = fn_get_type(file, fn);
			*next = paren + 1;
			node_dst->fn_name = xmemdupz(fn, (size_t)(fn_end - fn));
			node_dst->fn_args = fn_args_get(paren, paren_end(paren, paren + strlen(paren)));
			return 1;
		}
	}
	return 0;
}

/* TODO: sort linked list of declared functions based on the length of the function name
 * so we can skip comparions with called functions that are too dissimilar. */

void
cvt_buffer_to_nodes(fnlist_ty *decl_head, fnlist_ty *cal_head, jtrie_ty *trie_head, const char *file, int first_pass)
{
	const char *p = file;
	const char *p_next;
	fnlist_ty *decl_node = decl_head, *cal_node = cal_head;
	fnlist_ty node_dst;
	fn_mode_ty fn_mode;
	int fn_id = 1;
	for (; (fn_get(p, &p_next, &fn_mode, &node_dst, file)); p = p_next, ++fn_id) {
		/* Ignore called functions on the second pass
		 * since we only check for declarations. */
		if (!first_pass && fn_mode == FN_CALLED)
			goto next;
		if (fn_mode == FN_DECLARED) {
			assert(jtrie_insert(trie_head, node_dst.fn_name) == JTRIE_RET_SUCC);
			fnlist_insert_tail(&decl_node, node_dst.fn_name, node_dst.fn_args, fn_id);
		} else if (first_pass /* && fn_mode == FN_CALLED */) {
			/* Add function declarations to the linked list. */
			fnlist_insert_tail(&cal_node, node_dst.fn_name, node_dst.fn_args, fn_id);
		} else {
next:
			free(node_dst.fn_name);
			llist_free(node_dst.fn_args);
		}
	}
}

#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)

int
cfreq_diff(const char *s, const char *t)
{
	int t1[JTRIE_ASCII_SIZE] = { 0 }, t2[JTRIE_ASCII_SIZE] = { 0 };
	int diff = 0;
	for (; *s; ++s)
		++t1[JTRIE_ASCII_IDX_GET(*s)];
	for (; *t; ++t)
		++t2[JTRIE_ASCII_IDX_GET(*t)];
	for (int i = 0; i < JTRIE_ASCII_SIZE; ++i)
		diff += MAX(t1[i], t2[i]) - MIN(t1[i], t2[i]);
	return diff;
}

#define MIN3(x, y, z) (((x) < (y)) ? ((x) < (z) ? (x) : (z)) : ((y) < (z) ? (y) : (z)))

int
dld(const char *s, int m, const char *t, int n)
{
	int tbl[n + 1][m + 1];
	tbl[0][0] = 0;
	for (int i = 1; i <= n; ++i)
		tbl[i][0] = tbl[i - 1][0] + 1;
	for (int j = 1; j <= m; ++j)
		tbl[0][j] = tbl[0][j - 1] + 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int sub_cost = s[j - 1] == t[i - 1] ? 0 : 1;
			tbl[i][j] = MIN3(tbl[i - 1][j] + 1, tbl[i][j - 1] + 1, tbl[i - 1][j - 1] + sub_cost);
			/* if (i > 1 && j > 1 && s[i - 1] == t[i - 2] && s[i - 2] == t[i - 1]) */
			/* 	tbl[i][j] = MIN(tbl[i][j], tbl[i - 2][j - 2] + sub_cost); */
		}
	return tbl[n][m];
}

#undef MIN3

#define CHAR_FREQ_DIFF_MAX(n) (n / 2)

fnlist_ty *
get_most_similar_string(fnlist_ty *decl_head, const char *s, int max_lev, int *dist)
{
	fnlist_ty *node, *min_node;
	int min_lev = INT_MAX;
	int s_len = strlen(s);
	for (node = decl_head, min_node = decl_head; node->next; fnlist_next(node)) {
		int val_len = (int)strlen(node->fn_name);
		/* If the character frequency difference is too large, don't calculate LD. */
		if (MAX(s_len, val_len) - MIN(s_len, val_len) <= CHAR_FREQ_DIFF_MAX(MIN(s_len, val_len))
		    && cfreq_diff(s, node->fn_name) <= CHAR_FREQ_DIFF_MAX(MIN(s_len, val_len))) {
			int lev = dld(node->fn_name, val_len, s, s_len);
			if (lev < min_lev) {
				min_lev = lev;
				min_node = node;
			}
		}
	}
	*dist = min_lev;
	return (min_lev > max_lev) ? NULL : min_node;
}

#undef CHAR_FREQ_DIFF_MAX

const char *standard_headers[] = {
	"/usr/include/assert.h",
	"/usr/include/complex.h",
	"/usr/include/ctype.h",
	"/usr/include/errno.h",
	"/usr/include/fenv.h",
	"/usr/include/float.h",
	"/usr/include/inttypes.h",
	"/usr/include/iso646.h",
	"/usr/include/limits.h",
	"/usr/include/locale.h",
	"/usr/include/math.h",
	"/usr/include/setjmp.h",
	"/usr/include/signal.h",
	"/usr/include/stdalign.h",
	"/usr/include/stdarg.h",
	"/usr/include/stdatomic.h",
	"/usr/include/stdbool.h",
	"/usr/include/stddef.h",
	"/usr/include/stdint.h",
	"/usr/include/stdio.h",
	"/usr/include/stdlib.h",
	"/usr/include/stdnoreturn.h",
	"/usr/include/string.h",
	"/usr/include/tgmath.h",
	"/usr/include/threads.h",
	"/usr/include/time.h",
	"/usr/include/uchar.h",
	"/usr/include/wchar.h",
	"/usr/include/wctype.h"
};

#define PREPROCESS "cpp"

char *
file_preprocess_alloc(const char *fname)
{
	char tmpfile[] = "/tmp/XXXXXX";
	mktemp(tmpfile);
	char *cmd = xmalloc(strlen(PREPROCESS) + strlen(" ") + strlen(fname) + strlen(" > ") + strlen(tmpfile) + 1);
	strcpy(cmd, PREPROCESS);
	strcat(cmd, " ");
	strcat(cmd, fname);
	strcat(cmd, " > ");
	strcat(cmd, tmpfile);
	/* Execute "cpp fname > tmpfile" */
	assert(system(cmd) == 0);
	free(cmd);
	char *ret = file_alloc(tmpfile);
	assert(remove(tmpfile) == 0);
	return ret;
}

#undef PREPROCESS

void
file_preprocess_free(char *file)
{
	file_free(file);
}

#define LEV_MAX(n) (0.6 * n)

int
do_autosuggest(fnlist_ty **cal_head, fnlist_ty *decl_head, fnlist_ty *unfound_head, jtrie_ty *trie_head, const char *file, const char *fname, int first_pass)
{
	cvt_buffer_to_nodes(decl_head, *cal_head, trie_head, file, first_pass);
	fnlist_ty *cal_node, *cal_prev = NULL, *unfound_node = unfound_head;
	for (cal_node = *cal_head; cal_node->next;) {
		/* Check trie for exact match. If a match is found,
		 * either the called function is declared or it has
		 * been checked. */
		if (!jtrie_match(trie_head, cal_node->fn_name)) {
			/* Add called functions to the trie so multiple occurences
			 * of the same function will only be checked once. */
			assert(jtrie_insert(trie_head, cal_node->fn_name) == JTRIE_RET_SUCC);
			int lev;
			int val_len = strlen(cal_node->fn_name);
			fnlist_ty *similar = get_most_similar_string(decl_head, cal_node->fn_name, LEV_MAX(val_len), &lev);
			if (similar) {
				if (!first_pass) {
					int min;
					/* Point to the location of the integer in the string.
					 * The format is
					 * unfound_node->fn_name = "function_name\0similar_function_name\0filename\edit_distance" */
					char *min_p = cal_node->fn_name + strlen(cal_node->fn_name) + 1;
					min_p += strlen(min_p) + 1;
					min_p += strlen(min_p) + 1;
					/* Read the integer from the string. */
					memcpy(&min, min_p, sizeof(int));
					if (lev < min) {
						cal_node->fn_name = xrealloc(cal_node->fn_name, strlen(cal_node->fn_name) + 1 + strlen(similar->fn_name) + 1 + strlen(fname) + 1 + sizeof(int));
						char *p = cal_node->fn_name + strlen(cal_node->fn_name) + 1;
						strcpy(p, similar->fn_name);
						p += strlen(p) + 1;
						strcpy(p, fname);
						p += strlen(p) + 1;
						/* Write the integer to the string.
						 * Safe version of *(int *)p = i;
						 * since p may be unaligned. */
						memcpy(p, &lev, sizeof(lev));
					}
				} else {
					if (lev > 0)
						printf("\"%s\" is an undeclared function. Did you mean \"%s\"?\n", cal_node->fn_name, similar->fn_name);
				}
			} else if (first_pass) {
				/* Add called functions whose declaration we can not find in the current file. */
				int i = INT_MAX;
				char *tmp = xmalloc(strlen(cal_node->fn_name) + 1 + strlen("?") + 1 + strlen("?") + 1 + sizeof(int));
				char *p = tmp;
				strcpy(p, cal_node->fn_name);
				p += strlen(cal_node->fn_name) + 1;
				memcpy(p, "?\0?\0", 4);
				p += 4;
				memcpy(p, &i, sizeof(i));
				fnlist_insert_tail(&unfound_node, tmp, llist_dup(cal_node->fn_args), cal_node->fn_id);
			}
		} else {
			if (!first_pass) {
				printf("\"%s\" is an undeclared function. Did you mean to include \"%s\"?\n", cal_node->fn_name, fname);
				/* Remove called functions we found from the linked list */
				fnlist_ty *next = cal_node->next;
				fnlist_delete_curr(cal_head, cal_node, cal_prev);
				cal_node = next;
				continue;
			}
		}
		cal_prev = cal_node;
		fnlist_next(cal_node);
	}
	if (!first_pass)
		unfound_head = *cal_head;
	int cnt = 0;
	/* Remove unfound functions from the trie so they will not be skipped in the second pass. */
	for (unfound_node = unfound_head; unfound_node->next; fnlist_next(unfound_node), ++cnt)
		jtrie_delete(trie_head, unfound_node->fn_name);
	/* Check if the list of unfound functions is empty. */
	return cnt;
}

int
do_autosuggest2(fnlist_ty **decl_head, fnlist_ty **unfound_head, jtrie_ty *trie_head, const char *fname)
{
	char *s = file_preprocess_alloc(fname);
	/* We don't need the declarations from the previous file, so free the linked list
	 * and initialize a new head. */
	fnlist_free(*decl_head);
	*decl_head = fnlist_alloc();
	int ret = do_autosuggest(unfound_head, *decl_head, NULL, trie_head, s, fname, 0);
	file_preprocess_free(s);
	return ret;
}

#include <dirent.h>

void
autosuggest(const char *fname)
{
	char *file = file_preprocess_alloc(fname);
	jtrie_ty *trie_head = jtrie_alloc();
	fnlist_ty *decl_head = fnlist_alloc(), *cal_head = fnlist_alloc(), *unfound_head = fnlist_alloc();
	int ret = do_autosuggest(&cal_head, decl_head, unfound_head, trie_head, file, fname, 1);
	file_preprocess_free(file);
	if (ret) {
		/* If we have unfound called functions which do not have similar matches in the input file,
		 * search for them in system headers. */
		for (int i = 0; i < (int)(sizeof(standard_headers) / sizeof(standard_headers[0])); ++i)
			/* Check if the system header exists. */
			if (access(standard_headers[i], R_OK) == 0) {
				do_autosuggest2(&decl_head, &unfound_head, trie_head, standard_headers[i]);
				if (!ret)
					break;
			}
		if (ret) {
			/* If the unfound linked list is still not empty, search for similar matches
			 * in the files in the directory of FNAME. */
			char *dir = strrchr(fname, '/');
			char *dirof_file_heap = NULL;
			char *dirof_file;
			if (dir)
				dirof_file = dirof_file_heap = xmemdupz(fname, (size_t)(dir - fname));
			else
				dirof_file = (char *)".";
			DIR *dp = opendir(dirof_file);
			assert(dp);
			struct dirent *ep;
			struct stat st;
			while ((ep = readdir(dp))) {
				const char *p = strrchr(ep->d_name, '.');
				/* Ignore non *.c and *.h files.
				 * Also ignore "." and "..". */
				if (!p || (tolower(*(p + 1)) != 'c' && tolower(*(p + 1)) != 'h') || *(p + 2) != '\0')
					continue;
				assert(stat(ep->d_name, &st) == 0);
				/* Ignore non-regular files. */
				if (!S_ISREG(st.st_mode))
					continue;
				do_autosuggest2(&decl_head, &unfound_head, trie_head, ep->d_name);
				if (!ret)
					break;
			}
			closedir(dp);
			free(dirof_file_heap);
		}
	}
	for (fnlist_ty *node = unfound_head; node->next; fnlist_next(node)) {
		const char *similar = node->fn_name + strlen(node->fn_name) + 1;
		const char *header = similar + strlen(similar) + 1;
		const char *dist_p = header + strlen(header) + 1;
		int dist;
		memcpy(&dist, dist_p, sizeof(int));
		/* unfound_node->fn_name = "function_name\0similar_function_name\0filename\edit_distance" */
		if (dist == INT_MAX)
			fprintf(stderr, "\"%s\" is an undeclared function.\n", node->fn_name);
		else
			fprintf(stderr, "\"%s\" is an undeclared function. Did you mean to call \"%s\" defined in \"%s\"?\n", node->fn_name, similar, header);
	}
	jtrie_free(&trie_head);
	fnlist_free(decl_head);
	fnlist_free(cal_head);
	fnlist_free(unfound_head);
}
