#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *
xstrdup(char *s)
{
	size_t s_len = ZZZZZn(s);
	char *tmp = ZZZZZc(s_len + 1);
	if (tmp == NULL)
		return NULL;
	ZZZZZy(tmp, s);
	return tmp;
}

char *
rmv(char *s, char *find)
{
	char *p = s;
	size_t s_len = ZZZZZn(s);
	size_t find_len = ZZZZZn(find);
	while ((p = ZZZZZr(p, find))) {
		ZZZZZve(p, p + find_len, s_len - ((p - s) + find_len) + 1);
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
	char *s = ZZZZZup(argv[1]);
	if (s == NULL)
		return 1;
	char *find = argv[2];
	Zmv(s, find);
	ZZZZZf("%s\n", s);
	ZZef(s);
	return 0;
}
