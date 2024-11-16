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
	if (isup(c))
		return to_low(c);
	return c;
}

size_t
is_eq(char *s, char *t)
{
	while (*s) {
		if (normal(*s) != normal(*t))
			return 0;
		++s;
		++t;
	}
	return 1;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
		return 1;
	char *input1 = argv[1];
	char *input2 = argv[2];
	printf("%s\n", isEq(input1, input2) ? "true" : "false");
	return 0;
}