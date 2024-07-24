#include <stdio.h>
#include <sys/stat.h>
#include "lib.c"

/* #define FNAME "_example.h" */
#define FNAME "lib.c"

int
main()
{
	char *s = cs_file_read_alloc(FNAME);
	fns_ty *decl_head = cs_fns_alloc(), *cal_head = cs_fns_alloc();
	fns_ty *decl_node, *cal_node;
	cs_fns_read_from_file(decl_head, cal_head, s);

	puts("Declared functions:");
	for (decl_node = decl_head; decl_node; decl_node = decl_node->next)
		if (decl_node->value)
			puts(decl_node->value);
	puts("\n");
	puts("Called functions:");
	for (cal_node = cal_head; cal_node; cal_node = cal_node->next)
		if (cal_node->value)
			puts(cal_node->value);

/* 	for (cal_node = cal_head; cal_node; cal_node = cal_node->next) */
/* 		if (cal_node->value) { */
/* 			puts(cal_node->value); */
/* 			fns_ty *similar = cs_fns_get_most_similar_string(decl_head, cal_node->value, 0); */
/* 			if (similar) */
/* 				puts(similar->value); */
/* 			puts("==="); */
/* 		} */

	cs_file_read_free(s);
	cs_fns_freeall(decl_head);
	cs_fns_freeall(cal_head);
	return 0;
}
