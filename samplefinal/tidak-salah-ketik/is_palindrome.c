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
	if (isupp(c))
		return tolow(c);
	return c;
}

int palind(char *s)
{
	char *s_e = s + strlen(s) - 1;
	while (s < s_e) {
		if (norm(*s) != norm(*s_e))
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
	printf("%s\n", palind(input) ? "true" : "false");
	return 0;
}
