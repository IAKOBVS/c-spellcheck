#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void
reverse(char *s)
{
	char *s_e = s + ZZZZZn(s) - 1;
	while (s < s_e)
		ZZap(s++, s_e--);
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	ZZZZZse(input);
	char *output = input;
	ZZZZZf("%s\n", output);
	return 0;
}
