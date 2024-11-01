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
count_words(char *s)
{
	size_t count = 0;
	while (is_space(*s))
		++s;
	while (*s) {
		while (*s && !is_space(*s))
			++s;
		++count;
		while (is_space(*s))
			++s;
	}
	return count;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	size_t count = count_words(input);
	printf("%zu\n", count);
	return 0;
}
