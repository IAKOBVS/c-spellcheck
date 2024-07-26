#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>

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
		case '"':
			++src;
			for (;;) {
				switch (*src) {
				default:
					++src;
					break;
				case '\0':
					goto at_nul;
				case '\\':
					++src;
					if (*src == '\"')
						++src;
					break;
				case '"':
					++src;
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

/* TODO: have a more robust way of checking whether a function is declared or called. */

fn_ty
fn_get_type(const char *s, const char *end)
{
	const char *line = xmemrchr(s, '\n', (size_t)(end - s));
	line = (line != NULL) ? line + 1 : s;
	return (*line == '\t' || *line == ' ') ? FN_CALLED : FN_DECLARED;
}

char *
fn_get(const char *s, const char **next, const char **fn_end, fn_ty *fn_type)
{
	const char *fn, *paren, *p;
	for (p = s;; p = paren + 1) {
		paren = strchr(p, '(');
		if (!paren)
			break;
		fn = fn_start(s, paren, fn_end);
		if (fn) {
			*fn_type = fn_get_type(s, fn);
			*next = paren + 1;
			return (char *)fn;
		}
	}
	return NULL;
}

#define ll_next(node) node = (node)->next

ll_ty *
ll_alloc()
{
	return xcalloc(sizeof(ll_ty));
}

void
ll_node_free(ll_ty *node)
{
	free(node->value);
	free(node);
}

void
ll_free(ll_ty *node)
{
	if (node) {
		ll_free(node->next);
		ll_node_free(node);
	}
}

void
ll_insert_head(ll_ty **head, char *value)
{
	ll_ty *old_head = *head;
	*head = xmalloc(sizeof(ll_ty));
	(*head)->value = value;
	(*head)->next = old_head;
}

void
ll_insert_tail(ll_ty **tail, char *value)
{
	(*tail)->value = value;
	(*tail)->next = ll_alloc();
	ll_next(*tail);
}

void
ll_delete_curr(ll_ty **head, ll_ty *node, ll_ty *prev)
{
	if (prev)
		prev->next = node->next;
	else
		*head = node->next;
	ll_node_free(node);
}

void
ll_delete(ll_ty **head, ll_ty *target)
{
	ll_ty *node = *head, *prev = NULL;
	for (; node != target; ll_next(node))
		prev = node;
	ll_delete_curr(head, node, prev);
}

/* TODO: sort linked list of declared functions based on the length of the function name
 * so we can skip comparions with called functions that are too dissimilar. */

void
cvt_buffer_to_nodes(ll_ty *decl_head, ll_ty *cal_head, jtrie_node_ty *trie_head, const char *file, int first_pass)
{
	const char *p = file;
	const char *p_next, *fn_end;
	ll_ty *decl_node = decl_head, *cal_node = cal_head;
	fn_ty fn_type;
	for (char *val; (val = fn_get(p, &p_next, &fn_end, &fn_type)); p = p_next) {
		/* Ignore called functions on the second pass
		 * since we only check for declarations. */
		if (!first_pass && fn_type == FN_CALLED)
			continue;
		val = xmemdupz(val, (size_t)(fn_end - val));
		if (fn_type == FN_DECLARED) {
			assert(jtrie_insert(trie_head, val) == JTRIE_RET_SUCC);
			ll_insert_tail(&decl_node, val);
		} else if (first_pass /* && fn_type == FN_CALLED */) {
			/* Add function declarations to the linked list. */
			ll_insert_tail(&cal_node, val);
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

/* TODO: implement DLD. */

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

#undef MIN3

#define CHAR_FREQ_DIFF_MAX(n) (n / 2)

ll_ty *
get_most_similar_string(ll_ty *decl_head, const char *s, int max_lev, int *dist)
{
	ll_ty *node, *min_node;
	int min_lev = INT_MAX;
	int s_len = strlen(s);
	for (node = decl_head, min_node = decl_head; node->next; ll_next(node)) {
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
do_autosuggest(ll_ty **cal_head, ll_ty *decl_head, ll_ty *unfound_head, jtrie_node_ty *trie_head, const char *file, const char *fname, int first_pass)
{
	cvt_buffer_to_nodes(decl_head, *cal_head, trie_head, file, first_pass);
	ll_ty *cal_node, *cal_prev = NULL, *unfound_node = unfound_head;
	for (cal_node = *cal_head; cal_node->next;) {
		/* Check trie for exact match. If a match is found,
		 * either the called function is declared or it has
		 * been checked. */
		if (!jtrie_match(trie_head, cal_node->value)) {
			/* Add called functions to the trie so multiple occurences
			 * of the same function will only be checked once. */
			assert(jtrie_insert(trie_head, cal_node->value) == JTRIE_RET_SUCC);
			int lev;
			int val_len = strlen(cal_node->value);
			ll_ty *similar = get_most_similar_string(decl_head, cal_node->value, LEV_MAX(val_len), &lev);
			if (similar) {
				if (!first_pass) {
					int curr;
					char *curr_p = cal_node->value + strlen(cal_node->value) + 1;
					curr_p += strlen(curr_p) + 1;
					curr_p += strlen(curr_p) + 1;
					memcpy(&curr, curr_p, sizeof(int));
					if (lev < curr) {
						/* unfound_node->value = "function_name\0similar_function_name\0filename\edit_distance" */
						cal_node->value = xrealloc(cal_node->value, strlen(cal_node->value) + 1 + strlen(similar->value) + 1 + strlen(fname) + 1 + sizeof(int));
						char *p = cal_node->value + strlen(cal_node->value) + 1;
						strcpy(p, similar->value);
						p += strlen(p) + 1;
						strcpy(p, fname);
						p += strlen(p) + 1;
						memcpy(p, &lev, sizeof(lev));
					}
				} else {
					if (lev > 0)
						printf("\"%s\" is an undeclared function. Did you mean \"%s\"?\n", cal_node->value, similar->value);
				}
			} else if (first_pass) {
				/* Add called functions whose declaration we can not find in the current file. */
				int i = INT_MAX;
				char *tmp = xmalloc(strlen(cal_node->value) + 1 + strlen("?") + 1 + strlen("?") + 1 + sizeof(int));
				char *p = tmp;
				strcpy(p, cal_node->value);
				p += strlen(cal_node->value) + 1;
				memcpy(p, "?\0?\0", 4);
				p += 4;
				memcpy(p, &i, sizeof(i));
				ll_insert_tail(&unfound_node, tmp);
			}
		} else {
			if (!first_pass) {
				printf("\"%s\" is an undeclared function. Did you mean to include \"%s\"?\n", cal_node->value, fname);
				/* Remove called functions we found from the linked list */
				ll_ty *next = cal_node->next;
				ll_delete_curr(cal_head, cal_node, cal_prev);
				cal_node = next;
				continue;
			}
		}
		cal_prev = cal_node;
		ll_next(cal_node);
	}
	if (!first_pass)
		unfound_head = *cal_head;
	int cnt = 0;
	/* Remove unfound functions from the trie so they will not be skipped in the second pass. */
	for (unfound_node = unfound_head; unfound_node->next; ll_next(unfound_node), ++cnt)
		jtrie_delete(trie_head, unfound_node->value);
	/* Check if the list of unfound functions is empty. */
	return cnt;
}

void
autosuggest(const char *fname)
{
	char *file = file_preprocess_alloc(fname);
	jtrie_node_ty *trie_head = jtrie_alloc();
	ll_ty *decl_head = ll_alloc(), *cal_head = ll_alloc(), *unfound_head = ll_alloc();
	int ret = do_autosuggest(&cal_head, decl_head, unfound_head, trie_head, file, fname, 1);
	file_preprocess_free(file);
	if (ret)
		/* If we have unfound called functions which do not have similar matches in the input file,
		 * search for them in system headers. */
		for (int i = 0; i < (int)(sizeof(standard_headers) / sizeof(standard_headers[0])); ++i)
			/* Check if the system header exists. */
			if (access(standard_headers[i], R_OK) == 0) {
				char *s = file_preprocess_alloc(standard_headers[i]);
				/* We don't need the declarations from the previous file, so free the linked list
				 * and initialize a new head. */
				ll_free(decl_head);
				decl_head = ll_alloc();
				ret = do_autosuggest(&unfound_head, decl_head, NULL, trie_head, s, standard_headers[i], 0);
				file_preprocess_free(s);
				if (!ret)
					break;
			}
	for (ll_ty *node = unfound_head; node->next; ll_next(node)) {
		const char *similar = node->value + strlen(node->value) + 1;
		const char *header = similar + strlen(similar) + 1;
		/* unfound_node->value = "function_name\0similar_function_name\0filename\edit_distance" */
		fprintf(stderr, "\"%s\" is an undeclared function. Did you mean to call \"%s\" defined in \"%s\"?\n", node->value, similar, header);
	}
	jtrie_free(&trie_head);
	ll_free(decl_head);
	ll_free(cal_head);
	ll_free(unfound_head);
}
