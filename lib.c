#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>

#define JTRIE_ASCII_SIZE (('Z' - 'A') + ('z' - 'a') + ('9' - '0') + '1')
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
cs__fn_start(const char *start, const char *paren)
{
	const char *p = paren;
	while (--p >= start && (*p == ' ' || *p == '\t' || *p == '\n')) {}
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
	const char *fn, *paren, *p;
	for (p = s; (paren = strchr(p, '(')); p = paren + 1) {
		fn = cs__fn_start(s, paren);
		if (fn) {
			*fn_type = cs__fn_get_type(s, fn);
			*next = paren + 1;
			return xmemdupz(fn, (size_t)(paren - fn));
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

void cs_fns_read_from_buffer(fns_ty *decl_head, fns_ty *cal_head, jtrie_node_ty *trie_head, const char *file)
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

#define LEV_MAX(n) (0.6 * n) 

#undef MIN3

fns_ty *
cs_fns_get_most_similar_string(fns_ty *decl_head, const char *s, int max_lev, int *dist)
{
	fns_ty *node, *min_node;
	int min_lev = INT_MAX;
	int s_len = strlen(s);
	int lev;
	for (node = decl_head, min_node = decl_head; node; node = node->next)
		if (node->value && (lev = cs_lev(node->value, strlen(node->value), s, s_len)) < min_lev) {
			min_lev = lev;
			min_node = node;
		}
	*dist = min_lev;
	return (min_lev > max_lev) ? NULL : min_node;
}
