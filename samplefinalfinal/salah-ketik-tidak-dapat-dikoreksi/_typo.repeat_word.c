#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
repeat(char *s, int n)
{
	while (n--)
		ZZZZZr("%s", s);
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
		return 1;
	char *word = argv[1];
	size_t n = ZZZZZt(argv[2], NULL, 10);
	ZZZZZe(word, n);
	return 0;
}
