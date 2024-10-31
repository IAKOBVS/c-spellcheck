#include <stdio.h>

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

void
lower_str(char *s)
{
	while (*s) {
		if (isupp(*s))
			*s = tolow(*s);
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
	lower_str(output);
	printf("%s\n", output);
	return 0;
}
