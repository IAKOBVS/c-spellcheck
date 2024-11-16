//
// case.c
//
// Copyright 2013 Stephen Mathieson
// MIT licensed
//

#include <string.h>

int
is_lower(int c)
{
	return c >= 'a' && c <= 'z';
}

int
is_upper(int c)
{
	return c >= 'A' && c <= 'Z';
}

int
is_sep(int c)
{
	return c == '-' || c == '_' || c == ' ';
}

char *
case_upper(char *str)
{
	for (int i = 0, len = strlen(str); i < len; i++) {
		if (is_lower(str[i])) {
			str[i] -= 'a' - 'A';
		}
	}
	return str;
}

char *
case_lower(char *str)
{
	for (int i = 0, len = strlen(str); i < len; i++) {
		if (is_upper(str[i])) {
			str[i] += 'a' - 'A';
		}
	}
	return str;
}

char *
case_camel(char *str)
{
	for (int i = 0, len = strlen(str); i < len; i++) {
		if (is_sep(str[i])) {
			memmove(&str[i], &str[i + 1], len - i);
			// never cap the first char
			if (i && is_lower(str[i])) {
				str[i] -= 'a' - 'A';
			}
			// account for removing seperator
			i--;
			len--;
		}
	}

	return str;
}
