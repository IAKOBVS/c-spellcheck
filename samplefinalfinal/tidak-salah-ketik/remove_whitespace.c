#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
is_space(char c)
{
	switch (c) {
	case ' ':
	case '\n':
	case '\t':
	case '\r':
	case '\f':
		return 1;
	}
	return 0;
}

void
rmv_spc(char *s)
{
	char *dst = s;
	char *src = s;
	while (*src) {
		if (is_space(*src))
			++src;
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	char *output = input;
	rmv_spc(input);
	printf("%s\n", output);
	return 0;
}
