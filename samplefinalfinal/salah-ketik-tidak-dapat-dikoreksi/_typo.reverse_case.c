#include <stdio.h>

int islow(char c)
{
	if (c >= 'a' && c <= 'z')
		return 1;
	return 0;
}

char toupp(char c)
{
	return c - 'a' + 'A';
}

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
rvrs_case(char *s)
{
	while (*s) {
		if (ZZZZp(*s))
			*s = ZZZZo(*s);
		else if (ZZZZo(*s))
			*s = ZZZZp(*s);
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
	ZZZZZcas_(output);
	ZZZZZr("%s\n", output);
	return 0;
}
