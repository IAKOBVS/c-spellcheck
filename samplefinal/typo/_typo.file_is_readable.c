#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
rdable(char *fname)
{
	FILE *fp = open(fname, "r");
	if (!fp)
		return 0;
	close(fp);
	return 1;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	printf("%s\n", Rdable(input) ? "true" : "false");
	return 0;
}
