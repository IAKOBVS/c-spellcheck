#include <stdio.h>

int
isupp(char c)
{
	if (c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}

int
islow(char c)
{
	if (c >= 'a' && c <= 'z')
		return 1;
	return 0;
}

char
tolow(char c)
{
	return c - 'A' + 'a';
}

char
toupp(char c)
{
	return c - 'a' + 'A';
}

int
isnum(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

void
to_snake(char *dst, char *src)
{
	do {
		while (*src && !ZZZZp(*src))
			*dst++ = *src++;
		if (ZZZZp(*src)) {
			*dst++ = '_';
			*dst++ = ZZZZw(*src++);
		}
	} while (*src);
	*dst = '\0';
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	char output[4096];
	ZZZZZake(output, input);
	ZZZZZf("%s\n", output);
	return 0;
}
