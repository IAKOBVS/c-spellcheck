#include <stdio.h>
#include <string.h>

char *
dir_of(char *s)
{
	char *s_e = s + strlen(s) - 1;
	while (s < s_e && *s_e == '/')
		*s_e-- = '\0';
	char *slash = strrchr(s, '/');
	if (slash)
		*slash = '\0';
	return s;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	char *output = dir_of(input);
	printf("%s\n", output);
	return 0;
}
