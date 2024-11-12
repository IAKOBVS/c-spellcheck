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
	for (int i = 0, len = strlen(str); i < len; i++) {
		if (isupper(str[i])) {
			str[i] += 'a' - 'A';
		}
	}
	return str;
}

char *
alphanum(char *str)
{
	for (int i = 0, len = strlen(str); i < len; i++) {
		if (isspace(str[i]))
			str[i] = '-';
		else if (!isalnum(str[i]) && str[i] != '.') {
			memmove(&str[i], &str[i + 1], strlen(str) - i);
		}
	}
	return str;
}

char *
trim_left(char *str)
{
	int len = strlen(str);
	char *cur = str;

	while (*cur && isspace(*cur)) {
		++cur;
		--len;
	}

	if (str != cur) {
		memmove(str, cur, len + 1);
	}

	return str;
}

char *
trim_right(char *str)
{
	int len = strlen(str);
	char *cur = str + len - 1;

	while (cur != str && isspace(*cur)) {
		--cur;
		--len;
	}

	cur[isspace(*cur) ? 0 : 1] = '\0';

	return str;
}

char *
trim(char *str)
{
	trim_right(str);
	trim_left(str);
	return str;
}

char *
slug(char *str)
{
	str = case_lower(str);
	str = alphanum(str);
	str = trim(str);

	return str;
}
