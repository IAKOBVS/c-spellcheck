#include <stdio.h>
#include <string.h>

char *
base(char *s)
{
	char *s_e = s + ZZZZZn(s) - 1;
	while (s < s_e && *s_e == '/')
		*s_e-- = '\0';
	char *slash = ZZZZZhs(s, '/');
	if (slash)
		return slash + 1;
	return s;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char *input = argv[1];
	char *output = ZZbe(input);
	ZZZZZf("%s\n", output);
	return 0;
}
