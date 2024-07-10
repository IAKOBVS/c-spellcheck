#include "lib.c"
#include <stdio.h>
#include <sys/stat.h>
#define FNAME "/tmp/lib.c"
int
main()
{
	char *s = cs_read_file_alloc(FNAME);
	const char *p = s;
	const char *next;
	fns_ty *head = cs_fns_alloc();
	fns_ty *f = head;
	for (; (f->data = cs_fn_alloc(p, &next)); p = next) {
		f->next = cs_fns_alloc();
		f = f->next;
	}
	f = head;
	for (; f->data; f = f->next) {
		puts(f->data);
		if (!f->next)
			break;
	}
	cs_read_file_free(s);
	cs_fns_freeall(head);
	return 0;
}
