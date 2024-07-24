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

typedef struct ll_ty {
	char *value;
	struct ll_ty *next;
} ll_ty;

static void
remove_literal_strings(char *s)
{
	(void)s;
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
file_alloc(const char *fname)
{
	FILE *fp = fopen(fname, "r");
	assert(fp);
	struct stat st;
	assert(!stat(fname, &st));
	char *p = xmalloc((size_t)(st.st_size + 1));
	assert(fread(p, 1, (size_t)st.st_size, fp) == (size_t)st.st_size);
	assert(!fclose(fp));
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

static char *
fn_start(const char *start, const char *paren, const char **fn_end)
{
	const char *p = paren;
	while (--p >= start && (*p == ' ' || *p == '\t' || *p == '\n')) {}
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
	    || starts_with(p, "switch"))
		return NULL;
	return (char *)p;
}

fn_ty
fn_get_type(const char *s, const char *end)
{
	const char *line = xmemrchr(s, '\n', (size_t)(end - s));
	line = (line != NULL) ? line + 1 : s;
	return (*line == '\t' || *line == ' ') ? FN_CALLED : FN_DECLARED;
}

char *
fn_alloc(const char *s, const char **next, fn_ty *fn_type)
{
	const char *fn, *paren, *p, *end;
	for (p = s; (paren = strchr(p, '(')); p = paren + 1) {
		fn = fn_start(s, paren, &end);
		if (fn) {
			*fn_type = fn_get_type(s, fn);
			*next = paren + 1;
			return xmemdupz(fn, (size_t)(end - fn));
		}
	}
	return NULL;
}

ll_ty *
ll_alloc()
{
	return xcalloc(sizeof(ll_ty));
}

void
ll_node_free(ll_ty *p)
{
	free(p->value);
	free(p);
}

void
ll_free(ll_ty *p)
{
	if (p) {
		free(p->value);
		ll_free(p->next);
		free(p);
	}
}

void
ll_remove(ll_ty **head, ll_ty *target)
{
	ll_ty *node = *head, *prev = NULL;
	for (; node != target; node = node->next)
		prev = node;
	if (prev)
		prev->next = node->next;
	else
		*head = node->next;
	ll_node_free(node);
}

void
ll_cvt_buffer_to_nodes(ll_ty *decl_head, ll_ty *cal_head, jtrie_node_ty *trie_head, const char *file, int first_pass)
{
	const char *p = file;
	const char *next;
	ll_ty *decl_node = decl_head, *cal_node = cal_head;
	fn_ty fn_type;
	for (char *val; (val = fn_alloc(p, &next, &fn_type));) {
		if (fn_type == FN_DECLARED) {
			jtrie_add(trie_head, val);
			decl_node->value = val;
			decl_node->next = ll_alloc();
			decl_node = decl_node->next;
		} else if (first_pass /* && fn_type == FN_CALLED */) {
			/* Add function declarations to the linked list. */
			cal_node->value = val;
			cal_node->next = ll_alloc();
			cal_node = cal_node->next;
		}
		p = next;
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
ld(const char *s, int m, const char *t, int n)
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
		}
	return tbl[n][m];
}

#define CHAR_FREQ_DIFF_MAX(n) (n / 2)

#undef MIN3

ll_ty *
ll_get_most_similar_string(ll_ty *decl_head, const char *s, int max_lev, int *dist)
{
	ll_ty *node, *min_node;
	int min_lev = INT_MAX;
	int s_len = strlen(s);
	for (node = decl_head, min_node = decl_head; node; node = node->next)
		if (node->value) {
			int val_len = (int)strlen(node->value);
			/* If the character frequency difference is too large, don't calculate LD. */
			if (MAX(s_len, val_len) - MIN(s_len, val_len) <= CHAR_FREQ_DIFF_MAX(MIN(s_len, val_len))
			    && cfreq_diff(s, node->value) <= CHAR_FREQ_DIFF_MAX(MIN(s_len, val_len))) {
				int lev = ld(node->value, val_len, s, s_len);
				if (lev < min_lev) {
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

#define TMPFILE "./c-spellcheck-tmp2"

char *
file_preprocess_alloc(const char *fname)
{
	char *cmd = xmalloc(strlen("./preprocess ") + strlen(fname) + strlen(" > ") + strlen(TMPFILE) + 1);
	strcpy(cmd, "./preprocess ");
	strcat(cmd, fname);
	strcat(cmd, " > ");
	strcat(cmd, TMPFILE);
	system(cmd);
	free(cmd);
	return file_alloc(TMPFILE);
}

void
file_preprocess_free(const char *fname, char *file)
{
	assert(remove(TMPFILE) == 0);
	file_free(file);
	(void)fname;
}

#define LEV_MAX(n) (0.6 * n)

int
do_autosuggest(ll_ty **cal_head, ll_ty *decl_head, ll_ty *unfound_head, jtrie_node_ty *trie_head, const char *file, int first_pass)
{
	ll_cvt_buffer_to_nodes(decl_head, *cal_head, trie_head, file, first_pass);
	ll_ty *cal_node, *cal_prev = NULL, *unfound_node = unfound_head;
	for (cal_node = *cal_head; cal_node; cal_node = cal_node->next) {
		if (cal_node->value) {
			/* Check trie for exact match. If a match is found,
			 * either the called function is declared or it has
			 * been checked. */
			if (!jtrie_match(trie_head, cal_node->value)) {
				/* Add called functions to the trie so multiple occurences
				 * of the same function will only be checked once. */
				jtrie_add(trie_head, cal_node->value);
				int lev;
				int val_len = strlen(cal_node->value);
				ll_ty *similar = ll_get_most_similar_string(decl_head, cal_node->value, LEV_MAX(val_len), &lev);
				if (similar) {
					if (lev > 0)
						printf("\"%s\" is an undeclared function. Did you mean \"%s\"?\n", cal_node->value, similar->value);
					if (!first_pass) {
						/* Remove called functions we found from the linked list */
						if (cal_prev)
							cal_prev->next = cal_node->next;
						else
							*cal_head = cal_node->next;
						ll_node_free(cal_node);
						cal_node = NULL;
					}
				} else if (first_pass) {
					/* Add called functions whose declaration we can not find in the current file. */
					unfound_node->value = xmemdupz(cal_node->value, (size_t)val_len);
					unfound_node->next = ll_alloc();
					unfound_node = unfound_node->next;
				}
			}
		}
		cal_prev = cal_node;
	}
	/* unfound_head is passed as NULL */
	if (!first_pass)
		unfound_head = *cal_head;
	/* Remove unfound words from the trie so they will not be skipped in the second pass. */
	for (unfound_node = unfound_head; unfound_node; unfound_node = unfound_node->next) {
		if (unfound_node->value)
			jtrie_remove(trie_head, unfound_node->value);
	}
	return unfound_head->value != NULL;
}

void
autosuggest(const char *fname)
{
	char *file = file_alloc(fname);
	jtrie_node_ty *trie_head = jtrie_init();
	ll_ty *decl_head = ll_alloc(), *cal_head = ll_alloc(), *unfound_head = ll_alloc();
	if (do_autosuggest(&cal_head, decl_head, unfound_head, trie_head, file, 1))
		for (unsigned int i = 0; i < sizeof(standard_headers) / sizeof(standard_headers[0]); ++i) {
			if (access(standard_headers[i], F_OK) == 0) {
				char *s = file_preprocess_alloc(standard_headers[i]);
				file_preprocess_free(standard_headers[i], s);
				do_autosuggest(&unfound_head, decl_head, unfound_head, trie_head, standard_headers[i], 0);
			}
		}
	file_free(file);
	ll_free(decl_head);
	ll_free(cal_head);
	ll_free(unfound_head);
	jtrie_free(&trie_head);
}
