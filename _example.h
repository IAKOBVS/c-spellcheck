#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>

typedef struct fns_ty {
	char *value;
	struct fns_ty *next;
} fns_ty;

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
	p[n] = '\0';
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
cs__is_valid_fn_char(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static char *
cs__fn_start(const char *start, const char *curr)
{
	while (--curr >= start && (*curr == ' ' || *curr == '\t' || *curr == '\n')) {}
	for (; curr >= start && cs__is_valid_fn_char(*curr); --curr) {}
	++curr;
	if (!cs__is_valid_fn_char(*curr)
	    || cs__starts_with(curr, "if")
	    || cs__starts_with(curr, "for")
	    || cs__starts_with(curr, "while")
	    || cs__starts_with(curr, "switch"))
		return NULL;
	return (char *)curr;
}

char *
cs_fn_alloc(const char *s, const char **next)
{
	const char *fn_s, *fn_e, *p;
	p = s;
	for (; (fn_e = strchr(p, '(')); p = fn_e + 1) {
		fn_s = cs__fn_start(s, fn_e);
		if (fn_s) {
			*next = fn_e + 1;
			return xmemdupz(fn_s, (size_t)(fn_e - fn_s));
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
