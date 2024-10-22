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

enum status_ty {
	STATUS_NOSKIP = 0,
	STATUS_SKIP,
} status_ty;

enum algo_ty {
	ALGO_DLD,
	ALGO_TRIE,
	ALGO_GABUNGAN,
} algo_ty;

int algo = ALGO_GABUNGAN;

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

typedef struct type_ty {
	llist_ty *variables;
	char *value;
	struct type_ty *next;
} type_ty;

type_ty *types;

typedef struct fnlist_ty {
	char *fn_name;
	char *similar_fn_name;
	char *found_at;
	int lev;
	int fn_id;
	int is_typo;
	int is_typo_syn;
	int status;
	llist_ty *fn_args;
	struct fnlist_ty *next;
} fnlist_ty;

char *filename_target;
char *file_target;
fnlist_ty *decl_target_head;
fnlist_ty *cal_target_head;

llist_ty *
llist_find(llist_ty *head, const char *value)
{
	for (llist_ty *node = head; node->next; node = node->next)
		if (!strcmp(value, node->value))
			return node;
	return NULL;
}

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
	if (*src == '#')
		goto newline;
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
		case '\n':
			if (*(src + 1) == '#') {
newline:
				++src;
				for (; *src && *src != '\n'; ++src)
					;
			} else {
				*dst++ = *src++;
			}
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

void
type_node_free(type_ty *node)
{
	llist_free(node->variables);
	free(node->value);
	free(node);
}

void
type_free(type_ty *node)
{
	if (node) {
		type_free(node->next);
		type_node_free(node);
	}
}

type_ty *
type_alloc()
{
	return xcalloc(sizeof(type_ty));
}

void
type_insert_tail(type_ty **tail, char *value)
{
	(*tail)->value = value;
	(*tail)->variables = llist_alloc();
	(*tail)->next = type_alloc();
	*tail = (*tail)->next;
}

type_ty *
var_find(type_ty *head, const char *variable)
{
	for (type_ty *type_node = head; type_node->next; type_node = type_node->next)
		for (llist_ty *var_node = type_node->variables; var_node->next; var_node = var_node->next)
			if (!strcmp(variable, var_node->value))
				return type_node;
	return NULL;
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
	free(node->similar_fn_name);
	free(node->found_at);
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
	/* if (*p == ')') */
	/* 	while (--p >= start && xiswhite(*p)) {} */
	*fn_end = p + 1;
	for (; p >= start && is_fn_char(*p); --p) {}
	++p;
	if (!is_fn_char(*p)
	    || *p == '_'
	    || (*p >= '0' && *p <= '9')
	    || (*(*fn_end - 1) == 't' && *fn_end - p >= 2 && *(*fn_end - 2) == '_')
	    || starts_with(p, "if")
	    || starts_with(p, "for")
	    || starts_with(p, "while")
	    || starts_with(p, "return")
	    || starts_with(p, "switch")
	    || starts_with(p, "void")
	    || starts_with(p, "size_t")
	    || starts_with(p, "int")
	    || starts_with(p, "double")
	    || starts_with(p, "float")
	    || starts_with(p, "signed")
	    || starts_with(p, "unsigned")
	    || starts_with(p, "short")
	    || starts_with(p, "long")
	    || starts_with(p, "case")
	    || starts_with(p, "sizeof"))
		return NULL;
	return (char *)p;
}

/* TODO: have a more robust way of checking whether a function is declared or called.
 *       handle function pointers. */

/* TODO: handle function pointers (c_standard_lib/signal/raise.c) */

fn_mode_ty
fn_get_type(const char *s, const char *end)
{
	--end;
	for (; s <= end && (xiswhite(*end) || *end == '*'); --end) {}
	if (s <= end && is_fn_char(*end))
		return FN_DECLARED;
	return FN_CALLED;
}

char *
paren_end(const char *paren_s, const char *paren_e, char c_s, char c_e)
{
	const char *p = paren_s;
	if (*p == c_s) {
		int end_paren = 1;
		while (++p <= paren_e) {
			if (*p == c_e)
				--end_paren;
			else if (*p == c_s)
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
	for (; ++p <= paren_e;) {
		switch (*p) {
		case '\0':
paren_error:
			fprintf(stderr, "Unmatched parenthesis.\n");
			exit(EXIT_FAILURE);
			goto ret;
			break;
		case '(':
			p = paren_end(p, paren_e, '(', ')');
			assert(p);
			if (p == NULL)
				goto paren_error;
			break;
		case ')':
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
	const char *fn, *fn_end, *paren, *paren_e, *p;
	p = s;
	for (;;) {
		paren = strchr(p, '(');
		if (!paren)
			break;
		paren_e = paren_end(paren, paren + strlen(paren), '(', ')');
		if (!paren_e)
			break;
		const char *tmp = paren_e + 1;
		for (; *tmp && xiswhite(*tmp); ++tmp)
			;
		if (*tmp == '(') {
			p = tmp;
			continue;
		}
		fn = fn_start(s, paren, &fn_end);
		if (fn) {
			*fn_mode = fn_get_type(file, fn);
			*next = paren + 1;
			node_dst->fn_name = xmemdupz(fn, (size_t)(fn_end - fn));
			node_dst->fn_args = fn_args_get(paren, paren_e);
			/* For declared functions, remove the parameter name. */
			if (*fn_mode == FN_DECLARED) {
				for (llist_ty *node = node_dst->fn_args; node->next; node = node->next) {
					char *ptr = node->value + strlen(node->value) - 1;
					for (; ptr > node->value; --ptr) {
						if (!is_fn_char(*ptr)) {
							if (*ptr != '*') {
								*ptr = '\0';
								for (; ptr > node->value && xiswhite(*ptr); --ptr)
									*ptr = '\0';
							} else {
								*(ptr + 1) = '\0';
							}
							break;
						}
					}
				}
			}
			return 1;
		}
		p = paren + 1;
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
			if (decl_head) {
				if (trie_head) {
					if (algo == ALGO_TRIE || algo == ALGO_GABUNGAN) {
						jtrie_ty *node = jtrie_insert(trie_head, node_dst.fn_name);
						assert(node);
						node->id = fn_id;
						node->fn_args = node_dst.fn_args;
					}
				}
				fnlist_insert_tail(&decl_node, node_dst.fn_name, node_dst.fn_args, fn_id);
			} else {
				goto next;
			}
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
dld(const char *s, const char *t, int i, int j)
{
#if 0
	int tbl[j + 1][i + 1];
	tbl[0][0] = 0;
	for (int i = 1; i <= j; ++i)
		tbl[i][0] = tbl[i - 1][0] + 1;
	for (int j = 1; j <= i; ++j)
		tbl[0][j] = tbl[0][j - 1] + 1;
	for (int i = 1; i <= j; ++i)
		for (int j = 1; j <= i; ++j) {
			int sub_cost = s[j - 1] == t[i - 1] ? 0 : 1;
			tbl[i][j] = MIN3(tbl[i - 1][j] + 1, tbl[i][j - 1] + 1, tbl[i - 1][j - 1] + sub_cost);
			/* if (i > 1 && j > 1 && s[i - 1] == t[i - 2] && s[i - 2] == t[i - 1]) */
			/* 	tbl[i][j] = MIN(tbl[i][j], tbl[i - 2][j - 2] + sub_cost); */
		}
	return tbl[j][i];
#else
	int min = INT_MAX;
	if (i == 0 && j == 0) /* base case */
		min = MIN(min, 0);
	if (i > 0) /* deletion */
		min = MIN(min, dld(s, t, i - 1, j) + 1);
	if (j > 0) /* insertion */
		min = MIN(min, dld(s, t, i, j - 1) + 1);
	if (i > 0 && j > 0) /* substitution */
		min = MIN(min, dld(s, t, i - 1, j - 1) + (s[i - 1] != t[j - 1]));
	if (i > 1 && j > 1 && s[i - 1] == t[j - 2] && s[i - 2] == t[j - 1]) /* transposition */
		min = MIN(min, dld(s, t, i - 2, j - 2) + (s[i - 1] != t[j - 1]));
	return min;
#endif
}

#undef MIN3

#define CHAR_FREQ_DIFF_MAX(n) (n / 2)

fnlist_ty *
get_most_similar_fn_name_string(fnlist_ty *decl_head, const char *s, int max_lev, int *dist)
{
	fnlist_ty *node, *min_node;
	int min_lev = INT_MAX;
	int s_len = strlen(s);
	for (node = decl_head, min_node = decl_head; node->next; fnlist_next(node)) {
		int val_len = (int)strlen(node->fn_name);
		int lev = dld(node->fn_name, s, val_len, s_len);
		if (lev < min_lev) {
			min_lev = lev;
			min_node = node;
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

type_ty *
type_get(const char *s)
{
	type_ty *head = type_alloc();
	type_ty *node = head;
	type_insert_tail(&node, xstrdup("void"));
	type_insert_tail(&node, xstrdup("void *"));
	type_insert_tail(&node, xstrdup("void*"));
	type_insert_tail(&node, xstrdup("char"));
	type_insert_tail(&node, xstrdup("char *"));
	type_insert_tail(&node, xstrdup("char*"));
	type_insert_tail(&node, xstrdup("char*"));
	type_insert_tail(&node, xstrdup("int"));
	type_insert_tail(&node, xstrdup("short"));
	type_insert_tail(&node, xstrdup("long"));
	type_insert_tail(&node, xstrdup("float"));
	type_insert_tail(&node, xstrdup("double"));
	const char *s_s = s;
	const char *array[] = { "typedef", "struct", "enum", "union", NULL };
	for (int i = 0; array[i] != NULL; ++i) {
		s = s_s;
		for (; (s = strstr(s, array[i])); ++s) {
			if (!strcmp("typedef", array[i])) {
				s += strlen("typedef");
			} else {
				s += strlen(array[i]);
				const char *p = s;
				for (; p > s_s && xiswhite(*p); --p) {}
				if (p - s_s >= strlen("typedef") && starts_with(p - strlen("typedef"), "typedef"))
					continue;
				while (xiswhite(*s))
					++s;
				const char *type_s = s;
				size_t len = 0;
				while (is_fn_char(*s)) {
					++s;
					++len;
				}
				if (len)
					type_insert_tail(&node, xmemdupz(type_s, len));
			}
			while (xiswhite(*s))
				++s;
			if (starts_with(s, "struct"))
				s += strlen("struct");
			else if (starts_with(s, "enum"))
				s += strlen("enum");
			else if (starts_with(s, "union"))
				s += strlen("union");
			while (xiswhite(*s))
				++s;
			if (*s == '{') {
				s = paren_end(s, s + strlen(s), '{', '}');
				assert(s);
				++s;
			}
			const char *p = strchr(s, ';');
			if (p && p > s) {
				--p;
				for (; p > s && xiswhite(*p); --p) {}
				const char *p_s = p;
				size_t len = 0;
				for (; p_s > s && is_fn_char(*p_s); --p_s, ++len) {}
				if (!is_fn_char(*p_s))
					++p_s;
				if (len)
					type_insert_tail(&node, xmemdupz(p_s, len));
			}
		}
	}
	return head;
}

void
var_get(const char *s, type_ty *types)
{
	const char *p = s;
	llist_ty *var_node;
	for (type_ty *n = types; n->next; n = n->next) {
		var_node = n->variables;
		p = s;
		for (; (p = strstr(p, n->value)); ++p) {
			p += strlen(n->value);
			while (xiswhite(*p))
				++p;
			if (*p != '{') {
				size_t len = 0;
				const char *p_s = p;
				while (xiswhite(*p))
					++p;
				for (; *p; ++p, ++len) {
					/* if (*p == ',') { */
					/* 	llist_insert_tail(&var_node, xmemdupz(p_s, len)); */
					/* 	while (xiswhite(*p)) */
					/* 		++p; */
					/* 	len = 0; */
					/* 	p_s = p; */
					/* } */
					if (len) {
						while (xiswhite(*p))
							++p;
					}
					if (*p == ';' || *p == '=' || *p == '[' || *p == ')' || *p == '(' || *p == ',') {
						llist_insert_tail(&var_node, xmemdupz(p_s, len));
						break;
					}
				}
			}
		}
	}
}

#define LEV_MAX(n) (0.6 * n)

int
do_autosuggest(fnlist_ty **cal_head, fnlist_ty *decl_head, fnlist_ty *notfound_head, jtrie_ty *trie_head, const char *file, const char *fname, int first_pass)
{
	cvt_buffer_to_nodes(decl_head, *cal_head, trie_head, file, first_pass);
	if (filename_target)
		cvt_buffer_to_nodes(NULL, cal_target_head, NULL, file_target, first_pass);
	fnlist_ty *cal_node, *notfound_node = notfound_head;
	for (cal_node = *cal_head; cal_node->next; fnlist_next(cal_node)) {
		if (cal_node->status == STATUS_SKIP)
			continue;
		int is_prefix = 0;
		if (algo == ALGO_DLD)
			goto dld;
		jtrie_ty *trie_node;
		/* Check trie for exact match. If a match is found,
		 * either the called function is declared or it has
		 * been checked. */
		trie_node = jtrie_match(trie_head, cal_node->fn_name);
		if (!trie_node) {
			char *tmp = NULL;
			/* Mark that a typo is found. */
			cal_node->is_typo = 1;
			/* Add called functions to the trie so multiple occurences
			 * of the same function will only be checked once. */
			/* assert(jtrie_insert(trie_head, cal_node->fn_name)); */
dld:;
			int lev;
			fnlist_ty similar_fn_name_stack;
			fnlist_ty *similar_fn_name;
			if (algo == ALGO_TRIE || algo == ALGO_GABUNGAN) {
				similar_fn_name = NULL;
				trie_node = jtrie_starts(trie_head, cal_node->fn_name);
				if (trie_node) {
					is_prefix = 1;
					int i;
					for (i = 0; i < JTRIE_ASCII_SIZE && !trie_node->child[i]; ++i) {}
					if (i < JTRIE_ASCII_SIZE) {
						size_t len = strlen(cal_node->fn_name);
						size_t actual_size = len + 2;
						tmp = malloc(actual_size);
						assert(tmp);
						strcpy(tmp, cal_node->fn_name);
						for (;;) {
							for (i = 0; i < JTRIE_ASCII_SIZE && !trie_node->child[i]; ++i) {}
							if (i == JTRIE_ASCII_SIZE)
								break;
							trie_node = trie_node->child[i];
							tmp = xrealloc(tmp, ++actual_size);
							assert(tmp);
							tmp[len] = i;
							tmp[++len] = '\0';
						}
						similar_fn_name = &similar_fn_name_stack;
						similar_fn_name->fn_name = tmp;
					} else {
						if (algo == ALGO_GABUNGAN)
							goto use_dld;
					}
				} else {
					if (algo == ALGO_GABUNGAN)
						goto use_dld;
				}
			} else {
use_dld:
				similar_fn_name = get_most_similar_fn_name_string(decl_head, cal_node->fn_name, LEV_MAX(strlen(cal_node->fn_name)), &lev);
				if (lev > 0)
					/* Mark that a typo is found. */
					cal_node->is_typo = 1;
			}
			if (similar_fn_name) {
				free(cal_node->similar_fn_name);
				cal_node->similar_fn_name = xstrdup(similar_fn_name->fn_name);
				if (!first_pass) {
					if (algo != ALGO_TRIE && !is_prefix && lev < cal_node->lev) {
						free(cal_node->found_at);
						cal_node->found_at = xstrdup(fname);
						cal_node->lev = lev;
					}
				} else {
					if (is_prefix || lev > 0) {
						printf("\"%s\" merupakan sebuah fungsi yang belum dideklarasi. Apakah yang dimaksud adalah \"%s\"?\n", cal_node->fn_name, similar_fn_name->fn_name);
						cal_node->status = STATUS_SKIP;
					}
				}
			} else if (first_pass) {
				/* Add called functions whose declaration we can not find in the current file. */
				notfound_node->lev = INT_MAX;
				fnlist_insert_tail(&notfound_node, xstrdup(cal_node->fn_name), llist_dup(cal_node->fn_args), cal_node->fn_id);
			}
			free(tmp);
		} else {
			if (fn_args_count(cal_node->fn_args) != fn_args_count(trie_node->fn_args)) {
				int is_variadic = 0;
				for (llist_ty *node = trie_node->fn_args; node->next; node = node->next) {
					/* variadic function */
					if (node->value && *(node->value) == '.')
						is_variadic = 1;
				}
				if (!is_variadic) {
					printf("\"%s(", cal_node->fn_name);
					fn_args_print(cal_node->fn_args);
					printf(")\"");
					printf(" merupakan sebuah pemanggilan dengan jumlah argumen yang tidak sesuai dengan deklarasinya, \"%s(", cal_node->fn_name);
					fn_args_print(trie_node->fn_args);
					printf(")\".\n");
					cal_node->is_typo_syn = 1;
					cal_node->status = STATUS_SKIP;
				}
			} else {
				for (llist_ty *n = cal_node->fn_args, *t_n = trie_node->fn_args; n->next && t_n->next; n = n->next, t_n = t_n->next) {
					if (starts_with(n->value, "_")
					|| starts_with(n->value, "stdin")
					|| starts_with(n->value, "stdout")
					|| starts_with(n->value, "stderr")
					|| *(n->value + strcspn(n->value, "*&+-=.'\"?:()0123456789")))
						continue;
					type_ty *type_node = var_find(types, n->value);
					if (!type_node) {
						printf("\"%s(", cal_node->fn_name);
						fn_args_print(cal_node->fn_args);
						printf(")\"");
						printf(" merupakan sebuah pemanggilan dengan variabel argumen, %s, yang belum dideklarasi.\n", n->value);
						cal_node->is_typo_syn = 1;
						cal_node->status = STATUS_SKIP;
					} else if (strcmp(type_node->value, t_n->value)
					           && !((starts_with(type_node->value, "char") || starts_with(type_node->value, "void"))
					                && (starts_with(type_node->value, "char") || starts_with(type_node->value, "void")))) {
						printf("\"%s(", cal_node->fn_name);
						fn_args_print(cal_node->fn_args);
						printf(")\"");
						printf(" merupakan sebuah pemanggilan dengan variabel argumen, %s, dengan tipe argumen yang salah (%s, seharusnya %s).\n", n->value, type_node->value, t_n->value);
						cal_node->is_typo_syn = 1;
						cal_node->status = STATUS_SKIP;
					}
				}
			}
			if (!first_pass) {
				printf("\"%s\" merupakan sebuah fungsi yang belum dideklarasi. Apakah dimaksudkan untuk meng-include header \"%s\"?\n", cal_node->fn_name, fname);
				/* Mark called functions we found from the linked list */
				cal_node->status = STATUS_SKIP;
			} else {
				/* if (cal_node->fn_id < trie_node->id) */
				/* 	printf("\"%s\" dipanggil sebelum didefinisikan.\n", cal_node->fn_name); */
			}
		}
	}
	if (!first_pass)
		notfound_head = *cal_head;
	int cnt = 0;
	/* Remove notfound functions from the trie so they will not be skipped in the second pass. */
	for (notfound_node = notfound_head; notfound_node->next; fnlist_next(notfound_node), ++cnt)
		if (notfound_node->status != 1)
			++cnt;
	/* Check if the list of notfound functions is empty. */
	return cnt;
}

int
do_autosuggest_headers(fnlist_ty **decl_head, fnlist_ty **notfound_head, jtrie_ty *trie_head, const char *fname)
{
	char *s = file_preprocess_alloc(fname);
	/* We don't need the declarations from the previous file, so free the linked list
	 * and initialize a new head. */
	fnlist_free(*decl_head);
	*decl_head = fnlist_alloc();
	int ret = do_autosuggest(notfound_head, *decl_head, NULL, trie_head, s, fname, 0);
	file_preprocess_free(s);
	return ret;
}

typedef struct confusion_matrix_ty {
	int TP;
	int TN;
	int FP;
	int FN;
} confusion_matrix_ty;

/* TP: typo, correct autocorrection
   TN: no typo, no correction
   FP: typo, incorrect autocorrection
   FN: no typo, incorrect autocorrection */

void
confusion_make(confusion_matrix_ty *matrix, fnlist_ty *cal_head, fnlist_ty *cal_target_head)
{
	matrix->TP = 0;
	matrix->TN = 0;
	matrix->FP = 0;
	matrix->FN = 0;
	for (fnlist_ty *node = cal_head, *target_node = cal_target_head; node->next && target_node->next; node = node->next, target_node = target_node->next) {
		if (node->is_typo) {
			if (node->similar_fn_name && !strcmp(node->similar_fn_name, target_node->fn_name))
				++matrix->TP;
			else
				++matrix->FP;
		} else {
			++matrix->TN;
		}
	}
}

double
accuracy(confusion_matrix_ty *confusion_matrix)
{
	return (double)(confusion_matrix->TP + confusion_matrix->TN)
	       / (double)(confusion_matrix->TP + confusion_matrix->TN + confusion_matrix->FP + confusion_matrix->FN);
}

#include <dirent.h>

void
autosuggest(const char *fname)
{
	char *file = file_preprocess_alloc(fname);
	jtrie_ty *trie_head = (algo == ALGO_TRIE || algo == ALGO_GABUNGAN) ? jtrie_alloc() : NULL;
	fnlist_ty *decl_head = fnlist_alloc(), *cal_head = fnlist_alloc(), *notfound_head = fnlist_alloc();
	if (filename_target) {
		file_target = file_preprocess_alloc(filename_target);
		cal_target_head = fnlist_alloc();
	}
	types = type_get(file);
	var_get(file, types);
	/* for (type_ty *t = types; t->next; t = t->next) { */
	/* 	puts("type:"); */
	/* 	puts(t->value); */
	/* 	puts("vars:"); */
	/* 	for (llist_ty *v = t->variables; v->next; v = v->next) */
	/* 		puts(v->value); */
	/* } */
	int ret = do_autosuggest(&cal_head, decl_head, notfound_head, trie_head, file, fname, 1);
	file_preprocess_free(file);
	if (ret) {
		/* If we have notfound called functions which do not have similar matches in the input file,
		 * search for them in system headers. */
		for (int i = 0; i < (int)(sizeof(standard_headers) / sizeof(standard_headers[0])); ++i)
			/* Check if the system header exists. */
			if (access(standard_headers[i], R_OK) == 0) {
				do_autosuggest_headers(&decl_head, &notfound_head, trie_head, standard_headers[i]);
				if (!ret)
					break;
			}
		if (ret) {
			/* If the notfound linked list is still not empty, search for similar matches
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
				char *fulpath = malloc(strlen(dirof_file) + 1 + strlen(ep->d_name) + 1);
				assert(fulpath);
				strcpy(fulpath, dirof_file);
				strcat(fulpath, "/");
				strcat(fulpath, ep->d_name);
				assert(stat(fulpath, &st) == 0);
				/* Ignore non-regular files. */
				if (!S_ISREG(st.st_mode)) {
					free(fulpath);
					continue;
				}
				do_autosuggest_headers(&decl_head, &notfound_head, trie_head, fulpath);
				free(fulpath);
				if (!ret)
					break;
			}
			closedir(dp);
			free(dirof_file_heap);
		}
	}
	for (fnlist_ty *node = notfound_head; node->next; fnlist_next(node)) {
		if (node->lev == INT_MAX)
			fprintf(stderr, "\"%s\" merupakan sebuah fungsi yang belum dideklarasi.\n", node->fn_name);
		else
			fprintf(stderr, "\"%s\" merupakan sebuah fungsi yang belum dideklarasi. Apakah yang dimaksud adalah \"%s\" yang didefinisikan pada \"%s\"?\n", node->fn_name, node->similar_fn_name, node->found_at);
	}
	if (filename_target) {
		confusion_matrix_ty confusion_matrix;
		confusion_make(&confusion_matrix, cal_head, cal_target_head);
		double acc = accuracy(&confusion_matrix);
		printf("TP: %d\n", confusion_matrix.TP);
		printf("TN: %d\n", confusion_matrix.TN);
		printf("FP: %d\n", confusion_matrix.FP);
		printf("FN: %d\n", confusion_matrix.FN);
		printf("ACC: %f\n", acc);
		(void)acc;
	}
	type_free(types);
	free(file_target);
	jtrie_free(&trie_head);
	fnlist_free(decl_head);
	fnlist_free(cal_head);
	fnlist_free(notfound_head);
	fnlist_free(cal_target_head);
}
