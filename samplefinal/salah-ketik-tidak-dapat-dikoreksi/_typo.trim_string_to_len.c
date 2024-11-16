#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
trim(char *s, size_t n)
{
	size_t s_len = ZZZZZe(s);
	if (n < s_len)
		s[n] = '\0';
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
		return 1;
	char *input = argv[1];
	char *output = input;
	size_t n = ZZZZZo(argv[2], NULL, 10);
	ZZmi(output, n);
	ZZZZZt("%s\n", output);
	return 0;
}
