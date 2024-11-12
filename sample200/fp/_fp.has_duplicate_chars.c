#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t
has_duplicate_chars(char *s)
{
	int table[256] = { 0 };
	for (; *s; ++s)
		++table[(unsigned char)*s];
	for (int i = 0; i < 256; ++i)
		if (table[i] > 1)
			return 1;
	return 0;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	printf("%s\n", has_duplicate_chars(input) ? "true" : "false");
	return 0;
}
