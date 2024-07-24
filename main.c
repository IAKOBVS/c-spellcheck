#include <stdio.h>
#include <sys/stat.h>
#include "lib.c"

/* #define FNAME "_example.h" */
#define FNAME "lib.c"

int
main()
{
	char *s = cs_file_read_alloc(FNAME);
	jtrie_node_ty *trie_head = jtrie_init();
	fns_ty *decl_head = cs_fns_alloc(), *cal_head = cs_fns_alloc();
	fns_ty *decl_node, *cal_node;
	cs_fns_read_from_buffer(decl_head, cal_head, trie_head, s);

	(void)decl_node;

	for (cal_node = cal_head; cal_node; cal_node = cal_node->next)
		if (cal_node->value) {
			/* Check trie for exact match. If a match is found,
			 * either the called function is declared or it has
			 * been checked. */
			if (!jtrie_match(trie_head, cal_node->value)) {
				int lev;
				fns_ty *similar = cs_fns_get_most_similar_string(decl_head, cal_node->value, LEV_MAX(strlen(cal_node->value)), &lev);
				if (similar) {
					if (lev > 0)
						printf("%s is an undeclared function. Did you mean %s?\n", cal_node->value, similar->value);
				} else {
					printf("%s is an undeclared function.\n", cal_node->value);
				}
				/* Add called function to trie so multiple occurences of
				 * the same called functions will only be checked once. */
				jtrie_add(trie_head, cal_node->value);
			}
		}

	cs_file_read_free(s);
	cs_fns_freeall(decl_head);
	cs_fns_freeall(cal_head);
	jtrie_free(&trie_head);
	return 0;
}
