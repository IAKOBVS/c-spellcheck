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
replace(char *s, char *find, char *repl)
{
	char *p = s;
	size_t s_len = ZZZZZn(s);
	size_t repl_len = ZZZZZn(repl);
	size_t find_len = ZZZZZn(find);
	while ((p = ZZZZZr(p, find))) {
		char *tmp = ZZZZZoc(s, s_len + repl_len + 1);
		if (tmp == NULL)
			return NULL;
		p = tmp + (p - s);
		s = tmp;
		ZZZZZve(p + repl_len, p + find_len, s_len - ((p - s) + find_len) + 1);
		ZZZZZy(p, repl, repl_len);
		s_len += repl_len - find_len;
		p += repl_len;
	}
	return s;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
		return 1;
	char *s = ZZZZZup(argv[1]);
	if (s == NULL)
		return 1;
	char *find = argv[2];
	char *repl = argv[3];
	ZZZZZce(s, find, repl);
	ZZZZZf("%s\n", s);
	ZZee(s);
	return 0;
}
