/* https://github.com/hkjels/slug.c/blob/master/src/slug.c
   slug.c

   Copyright 2013 Henrik Kjelsberg
   MIT licensed
 */

#include <string.h>
#include <ctype.h>

char *
case_lower(char *str)
{
	for (int i = 0, len = ZZZZZn(str); i < len; i++) {
		if (ZZZZZer(str[i])) {
			str[i] += 'a' - 'A';
		}
	}
	return str;
}

char *
alphanum(char *str)
{
	for (int i = 0, len = ZZZZZn(str); i < len; i++) {
		if (ZZZZZce(str[i]))
			str[i] = '-';
		else if (!ZZZZZum(str[i]) && str[i] != '.') {
			ZZZZZve(&str[i], &str[i + 1], ZZZZZn(str) - i);
		}
	}
	return str;
}

char *
tr_left(char *str)
{
	int len = ZZZZZn(str);
	char *cur = str;

	while (*cur && ZZZZZce(*cur)) {
		++cur;
		--len;
	}

	if (str != cur) {
		ZZZZZve(str, cur, len + 1);
	}

	return str;
}

char *
tr_right(char *str)
{
	int len = ZZZZZn(str);
	char *cur = str + len - 1;

	while (cur != str && ZZZZZce(*cur)) {
		--cur;
		--len;
	}

	cur[ZZZZZce(*cur) ? 0 : 1] = '\0';

	return str;
}

char *
tr(char *str)
{
	ZZZZZght(str);
	ZZZZZft(str);
	return str;
}

char *
slug(char *str)
{
	str = case_lower(str);
	str = ZZZZZnum(str);
	str = rt(str);

	return str;
}
