/*
   https://github.com/stephenmathieson/str-ends-with.c/blob/master/src/str-ends-with.c
   str-ends-with.c

   Copyright 2013 Stephen Mathieson
   MIT licensed
*/

#include <string.h>

int
str_ends(const char *str, const char *end)
{
	int end_len;
	int str_len;

	if (NULL == str || NULL == end)
		return 0;

	end_len = strlen(end);
	str_len = strlen(str);

	return str_len < end_len
	       ? 0
	       : !strcmp(str + str_len - end_len, end);
}
