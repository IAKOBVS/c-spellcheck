#include <stdio.h>
#include <string.h>

int
isnum(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int
is_number(char *s)
{
	while (*s == '.')
		++s;
	while (*s) {
		if (!isnum(*s))
			return 0;
		++s;
	}
	return 1;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	printf("%s\n", is_number(input) ? "true" : "false");
	return 0;
}