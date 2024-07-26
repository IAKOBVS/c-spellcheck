#include <stdio.h>
#include <sys/stat.h>
#include "lib.c"

#define die_print(...)                        \
	do {                                  \
		fprintf(stderr, __VA_ARGS__); \
		exit(EXIT_FAILURE);           \
	} while (0)

#define ll_foreach(var, head) for (ll_ty *var = (head); (var)->next; ll_next(var))

int
main(int argc, char **argv)
{
	if (!argv[1] || !argv[1][0])
		die_print("Usage: %s <filename>\n", argv[0]);
	if (access(argv[1], R_OK) != 0)
		die_print("%s can not be read.", argv[1]);
	autosuggest(argv[1]);
	return 0;
	(void)argc;
}
