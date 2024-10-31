#include <stdio.h>
#include <sys/stat.h>
#include "lib.c"

#define die_print(...)                        \
	do {                                  \
		fprintf(stderr, __VA_ARGS__); \
		exit(EXIT_FAILURE);           \
	} while (0)

int
main(int argc, char **argv)
{
	if (!argv[1] || !argv[1][0])
		die_print("Usage: %s <filename>\n", argv[0]);
	const char *ext = strrchr(argv[1], '.');
	if (!ext)
		die_print("The first argument, %s, is not a C file.\n", argv[1]);
	if (access(argv[1], R_OK) != 0)
		die_print("%s can not be read.", argv[1]);
	for (int i = 2; i < argc; ++i)
		if (!strcmp("--dld", argv[i]))
			algo = ALGO_DLD;
		else if (!strcmp("--trie", argv[i]))
			algo = ALGO_TRIE;
		else if (!strcmp("--gabungan", argv[i]))
			algo = ALGO_GABUNGAN;
		else if (!strcmp("-v", argv[i]))
			VERBOSE = 1;
		else
			filename_target = argv[i];
#define FNAME argv[1]
	char tmp[4096];
	assert(strlen(FNAME) < 4096);
	strcpy(tmp, FNAME);
	chdir(dirname(tmp));
	strcpy(tmp, FNAME);
	autosuggest(basename(tmp));
	return 0;
	(void)argc;
}
