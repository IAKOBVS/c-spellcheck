#include <string.h>
#include <stdlib.h>
#include <assert.h>

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
	while (--curr >= start && cs__is_valid_fn_char(*curr)) {}
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

typedef struct fns_ty {
	char *data;
	struct fns_ty *next;
} fns_ty;

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
		cs_fn_free(p->data);
		cs_fns_freeall(p->next);
		cs_fns_free(p);
	}
}
