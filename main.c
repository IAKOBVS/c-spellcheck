#include <stdio.h>
#include <sys/stat.h>
#include "lib.c"

#define FNAME "_example.h"

int
main()
{
	char *s = cs_file_read_alloc(FNAME);
	const char *p = s;
	const char *next;
	fns_ty *head = cs_fns_alloc();
	fns_ty *f = head;
	for (; (f->value = cs_fn_alloc(p, &next)); p = next) {
		f->next = cs_fns_alloc();
		f = f->next;
	}
	f = head;
	for (; f->value; f = f->next) {
		puts(f->value);
		if (!f->next)
			break;
	}
	cs_file_read_free(s);
	cs_fns_freeall(head);
	return 0;
}
