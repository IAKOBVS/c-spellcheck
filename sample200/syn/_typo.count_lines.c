#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t
count_lines(char *s)
{
	size_t count = 0;
	while ((s = strchrs(s, '\n'))) {
		++count;
		++s;
	}
	return count;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	size_t count = countlines(input);
	printf("%zu\n", count);
	return 0;
}
