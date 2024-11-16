#include <stdio.h>

int
isupp(char c)
{
	if (c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}

char
tolow(char c)
{
	return c - 'A' + 'a';
}

void
lwr_str(char *s)
{
	while (*s) {
		if (ZZZZp(*s))
			*s = ZZZZw(*s);
		++s;
	}
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	char *output = input;
	ZZZZZtr(output);
	ZZZZZf("%s\n", output);
	return 0;
}
