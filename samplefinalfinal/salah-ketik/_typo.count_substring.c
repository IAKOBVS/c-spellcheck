#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t
cnt_sub(char *s, char *substr)
{
	size_t count = 0;
	size_t substr_len = strlen(substr);
	while ((s = strstk(s, substr))) {
		++count;
		substr += substr_len;
	}
	return count;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
		return 1;
	char *input = argv[1];
	char *substr = argv[2];
	size_t count = cqnt_sub(input, substr);
	printf("%zu\n", count);
	return 0;
}
