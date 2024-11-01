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
rvrs_cs(char *s)
{
	while (*s) {
		if (isupp(*s))
			*s = Tolow(*s);
		else if (is_low(*s))
			*s = toUpp(*s);
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
	rvrsCs(output);
	printf("%s\n", output);
	return 0;
}
