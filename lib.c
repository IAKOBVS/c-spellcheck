#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>

#define JTRIE_ASCII_SIZE    (('Z' - 'A') + ('z' - 'a') + ('9' - '0') + '1')
#define JTRIE_ASCII_IDX_GET jtrie__ascii_idx_get

static int
jtrie__ascii_idx_get(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c - 'A';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + ('Z' - 'A');
	if (c >= '0' && c <= '9')
		return c - '0' + ('Z' - 'A') + ('z' - 'a');
	/* else if (c == '_') */
	return ('Z' - 'A') + ('z' - 'a') + ('9' - '0');
}

#include "trie.h"

typedef enum fn_ty {
	FN_DECLARED,
	FN_CALLED
} fn_ty;

typedef struct fns_ty {
	char *value;
	struct fns_ty *next;
} fns_ty;

static void
cs__remove_literal_strings(char *s)
{
	char *dst = s;
	const char *src = s;
	for (; *src; ++src) {
		if (*src == '"' && (src - 1 < s || (*(src - 1) != '\\' && *(src - 1) != '\''))) {
			++src;
			for (;; ++src)
				if (*src == '"' && (*(src - 1) != '\\')) {
					break;
				} else if (*src == '\0') {
					fputs("Syntax error: unmatched quotation mark.\n", stderr);
					exit(EXIT_FAILURE);
				}
		} else {
			*dst++ = *src;
		}
	}
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

char *
cs_file_read_alloc(const char *fname)
{
	FILE *fp = fopen(fname, "r");
	assert(fp);
	struct stat st;
	assert(!stat(fname, &st));
	char *p = xmalloc((size_t)(st.st_size + 1));
	assert(fread(p, 1, (size_t)st.st_size, fp) == (size_t)st.st_size);
	assert(!fclose(fp));
	cs__remove_literal_strings(p);
	return p;
}

void
cs_file_read_free(char *s)
{
	free(s);
}

static int
cs__starts_with(const char *s, const char *with)
{
	return !strncmp(s, with, strlen(with));
}

static int
cs__is_fn_char(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static char *
cs__fn_start(const char *start, const char *paren, const char **fn_end)
{
	const char *p = paren;
	while (--p >= start && (*p == ' ' || *p == '\t' || *p == '\n')) {}
	*fn_end = p + 1;
	for (; p >= start && cs__is_fn_char(*p); --p) {}
	++p;
	if (!cs__is_fn_char(*p)
	    || *p == '_'
	    || (*p >= '0' && *p <= '9')
	    || cs__starts_with(p, "if")
	    || cs__starts_with(p, "for")
	    || cs__starts_with(p, "while")
	    || cs__starts_with(p, "return")
	    || cs__starts_with(p, "switch"))
		return NULL;
	return (char *)p;
}

fn_ty
cs__fn_get_type(const char *s, const char *end)
{
	const char *line = xmemrchr(s, '\n', (size_t)(end - s));
	line = (line != NULL) ? line + 1 : s;
	return (*line == '\t' || *line == ' ') ? FN_CALLED : FN_DECLARED;
}

char *
cs_fn_alloc(const char *s, const char **next, fn_ty *fn_type)
{
	const char *fn, *paren, *p, *end;
	for (p = s; (paren = strchr(p, '(')); p = paren + 1) {
		fn = cs__fn_start(s, paren, &end);
		if (fn) {
			*fn_type = cs__fn_get_type(s, fn);
			*next = paren + 1;
			return xmemdupz(fn, (size_t)(end - fn));
		}
	}
	return NULL;
}

void
cs_fn_free(char *s)
{
	free(s);
}

fns_ty *
cs_fns_alloc()
{
	return xcalloc(sizeof(fns_ty));
}

void
cs_fns_free(fns_ty *p)
{
	free(p);
}

void
cs_fns_freeall(fns_ty *p)
{
	if (p) {
		cs_fn_free(p->value);
		cs_fns_freeall(p->next);
		cs_fns_free(p);
	}
}

void
cs_fns_read_from_buffer(fns_ty *decl_head, fns_ty *cal_head, jtrie_node_ty *trie_head, const char *file)
{
	const char *p = file;
	const char *next;
	fns_ty *decl_node = decl_head, *cal_node = cal_head;
	fn_ty fn_type;
	for (char *val; (val = cs_fn_alloc(p, &next, &fn_type));) {
		if (fn_type == FN_DECLARED) {
			jtrie_add(trie_head, val);
			decl_node->value = val;
			decl_node->next = cs_fns_alloc();
			decl_node = decl_node->next;
		} else /* if (fn_type == FN_CALLED) */ {
			cal_node->value = val;
			cal_node->next = cs_fns_alloc();
			cal_node = cal_node->next;
		}
		p = next;
	}
}

#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)

int
cs_char_freq_diff(const char *s, const char *t)
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
cs_lev(const char *s, int m, const char *t, int n)
{
	for (; *s == *t && m; ++s, ++t, --m, --n) {}
	int tbl[m + 1][n + 1];
	int i, j;
	for (i = 0; i <= m; ++i)
		tbl[i][0] = i;
	for (i = 0; i <= n; ++i)
		tbl[0][i] = i;
	int sub_cost;
	for (i = 1; i <= m; ++i)
		for (j = 1; j <= n; ++j) {
			sub_cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
			tbl[i][j] = MIN3(tbl[i - 1][j] + 1,
			                 tbl[i][j - 1] + 1,
			                 tbl[i - 1][j - 1] + sub_cost);
		}
	return tbl[m][n];
}

#define LEV_MAX(n)            (0.6 * n)
#define CHAR_FREQ_DIFF_MAX(n) (n / 2)

#undef MIN3

fns_ty *
cs_fns_get_most_similar_string(fns_ty *decl_head, const char *s, int max_lev, int *dist)
{
	fns_ty *node, *min_node;
	int min_lev = INT_MAX;
	int s_len = strlen(s);
	int lev;
	int len;
	for (node = decl_head, min_node = decl_head; node; node = node->next)
		if (node->value) {
			len = (int)strlen(node->value);
			/* If the character frequency difference is too large, don't calculate LD. */
			if (cs_char_freq_diff(node->value, s) <= CHAR_FREQ_DIFF_MAX(len)) {
				if ((lev = cs_lev(node->value, len, s, s_len)) < min_lev) {
					min_lev = lev;
					min_node = node;
				}
			}
		}
	*dist = min_lev;
	return (min_lev > max_lev) ? NULL : min_node;
}

#include <ftw.h>
#include <unistd.h>

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

#define TMP_NAME "./c-spellcheck-tmp2"

int
cs__decl_exists_in_file(const char *fname, const char *fn, int fn_len)
{
	char *cmd = xmalloc(strlen("./preprocess ") + strlen(fname) + strlen(" > " TMP_NAME) + 1);
	strcpy(cmd, "./preprocess ");
	strcat(cmd, fname);
	strcat(cmd, " > " TMP_NAME);
	system(cmd);
	free(cmd);
	char *s = cs_file_read_alloc(TMP_NAME);
	const char *p = s;
	const char *q;
	while ((p = strstr(p, fn))) {
		if ((p == s || !cs__is_fn_char(*(p - 1))) && !cs__is_fn_char(*(p + fn_len))) {
			q = p + fn_len;
			for (; *q == ' ' || *q == '\t' || *q == '\n'; ++q) {}
			if (*q == '(' && cs__fn_get_type(s, p) == FN_DECLARED) {
				cs_file_read_free(s);
				return 1;
			}
		}
		p += fn_len;
	}
	cs_file_read_free(s);
	remove(TMP_NAME);
	return 0;
}

char *
cs_suggest_header_to_include(const char *fn, int fn_len, const char *dir)
{
	for (int i = 0; i < sizeof(standard_headers) / sizeof(standard_headers[0]); ++i)
		if (cs__decl_exists_in_file(standard_headers[i], fn, fn_len))
			return (char *)standard_headers[i];
	(void)dir;
	return NULL;
}

fns_ty *
autosuggest(fns_ty *cal_head, fns_ty *decl_head, jtrie_node_ty *trie_head, const char *file)
{
	cs_fns_read_from_buffer(decl_head, cal_head, trie_head, file);
	fns_ty *cal_node;
	for (cal_node = cal_head; cal_node; cal_node = cal_node->next)
		if (cal_node->value) {
			/* Check trie for exact match. If a match is found,
			 * either the called function is declared or it has
			 * been checked. */
			if (!jtrie_match(trie_head, cal_node->value)) {
				int lev;
				fns_ty *similar = cs_fns_get_most_similar_string(decl_head, cal_node->value, LEV_MAX(strlen(cal_node->value)), &lev);
				if (similar) {
					if (lev > 0)
						printf("\"%s\" is an undeclared function. Did you mean \"%s\"?\n", cal_node->value, similar->value);
				} else {
					const char *header = cs_suggest_header_to_include(cal_node->value, strlen(cal_node->value), "");
					if (header) {
						printf("\"%s\" is an undeclared function. Did you mean to include \"%s\"?\n", cal_node->value, header);
					} else {
						printf("\"%s\" is an undeclared function.\n", cal_node->value);
					}
				}
				/* Add called function to trie so multiple occurences of
				 * the same called functions will only be checked once. */
				jtrie_add(trie_head, cal_node->value);
			}
		}
	return 0;
}
