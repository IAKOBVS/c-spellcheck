#include <stdio.h>
#include <sys/stat.h>
#include "lib.c"

int
main(int argc, char **argv)
{
	assert(!argv[1] || argv[1][0]);

	char *file = cs_file_read_alloc(argv[1]);
	jtrie_node_ty *trie_head = jtrie_init();
	fns_ty *decl_head = cs_fns_alloc(), *cal_head = cs_fns_alloc();

	autosuggest(cal_head, decl_head, trie_head, file);

	cs_file_read_free(file);
	cs_fns_freeall(decl_head);
	cs_fns_freeall(cal_head);
	jtrie_free(&trie_head);

	return 0;
}
