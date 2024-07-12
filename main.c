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
	fns_ty *node;
	for (node = head; (node->value = cs_fn_alloc(p, &next)); node = node->next) {
		node->next = cs_fns_alloc();
		p = next;
	}
	for (node = head; node; node = node->next)
		if (node->value)
			puts(node->value);
	cs_file_read_free(s);
	cs_fns_freeall(head);
	return 0;
}
