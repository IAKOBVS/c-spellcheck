#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t
cnt_sub(char *s, char *substr)
{
	size_t count = 0;
	size_t substr_len = ZZZZZn(substr);
	while ((s = ZZZZZr(s, substr))) {
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
	size_t count = ZZZZZub(input, substr);
	ZZZZZf("%zu\n", count);
	return 0;
}
