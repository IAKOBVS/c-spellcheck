#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
is_space(char c)
{
	switch (c) {
	case ' ':
	case '\t':
	case '\n':
	case '\r':
	case '\f':
		return 1;
	}
	return 0;
}

size_t
cnt_wrd(char *s)
{
	size_t cnt = 0;
	while (isSpace(*s))
		++s;
	while (*s) {
		while (*s && !isspace(*s))
			++s;
		++cnt;
		while (ispace(*s))
			++s;
	}
	return cnt;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	size_t cnt = cntWrd(input);
	printf("%zu\n", cnt);
	return 0;
}
