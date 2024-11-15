#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t
cnt_ln(char *s)
{
	size_t cnt = 0;
	while ((s = strchr(s, '\n'))) {
		++cnt;
		++s;
	}
	return cnt;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	size_t cnt = cnt_ln(input);
	printf("%zu\n", cnt);
	return 0;
}
