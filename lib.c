#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>

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
	    || cs__starts_with(p, "if")
	    || cs__starts_with(p, "for")
	    || cs__starts_with(p, "while")
	    || cs__starts_with(p, "return")
	    || cs__starts_with(p, "switch"))
		return NULL;
	return (char *)p;
}

char *
cs_fn_alloc(const char *s, const char **next)
{
	const char *fn, *paren, *p;
	for (p = s; (paren = strchr(p, '(')); p = paren + 1) {
		fn = cs__fn_start(s, paren);
		if (fn) {
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
