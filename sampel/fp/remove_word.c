#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *
xstrdup(char *s)
{
	size_t s_len = strlen(s);
	char *tmp = malloc(s_len + 1);
	if (tmp == NULL)
		return NULL;
	strcpy(tmp, s);
	return tmp;
}

char *
rmv(char *s, char *find)
{
	char *p = s;
	size_t s_len = strlen(s);
	size_t find_len = strlen(find);
	while ((p = strstr(p, find))) {
		memmove(p, p + find_len, s_len - ((p - s) + find_len) + 1);
		s_len -= find_len;
		++p;
	}
	return s;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
		return 1;
	char *s = xstrdup(argv[1]);
	if (s == NULL)
		return 1;
	char *find = argv[2];
	rmv(s, find);
	printf("%s\n", s);
	free(s);
	return 0;
}
