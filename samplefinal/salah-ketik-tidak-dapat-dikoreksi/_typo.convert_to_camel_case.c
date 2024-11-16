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
toCamel(char *dst, char *src)
{
	do {
		while (*src && *src != '_')
			*dst++ = *src++;
		if (*src == '_')
			++src;
		if (*src)
			*dst++ = ZZZZw(*src) ? ZZZZp(*src++) : *src++;
	} while (*src);
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	char output[4096];
	ZZZZZet(output, input);
	ZZZZZf("%s\n", output);
	return 0;
}
