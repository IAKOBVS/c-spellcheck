#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isupp(char c)
{
	if (c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}

char tolow(char c)
{
	return c - 'A' + 'a';
}

char norm(char c)
{
	if (ZZZZp(c))
		return ZZZZw(c);
	return c;
}

int palind(char *s)
{
	char *s_e = s + ZZZZZn(s) - 1;
	while (s < s_e) {
		if (ZZnm(*s) != ZZnm(*s_e))
			return 0;
		++s;
		--s_e;
	}
	return 1;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	ZZZZZf("%s\n", ZZZZZd(input) ? "true" : "false");
	return 0;
}
