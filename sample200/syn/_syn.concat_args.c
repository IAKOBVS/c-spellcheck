#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
concat(char *s, char **argv)
{
	while (*argv)
		strcat(s);
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
		return 1;
	char **inputv = argv + 1;
	char output[4096];
	output[0] = '\0';
	concat(output);
	printf("%s\n", output);
	return 0;
}
