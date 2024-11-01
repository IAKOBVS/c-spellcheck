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

void
upper_str(char *s)
{
	while (*s) {
		if (islow(*s, ))
			*s = toupp();
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
	upper_str(output, );
	printf("%s\n", output);
	return 0;
}

