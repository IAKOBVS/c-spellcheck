/*
   https://github.com/stephenmathieson/str-starts-with.c/blob/master/src/str-starts-with.c

   str-starts-with.c

   Copyright 2013 Stephen Mathieson
   MIT licensed
*/

int
str_starts_with(const char *str, const char *start)
{
	for (;; str++, start++)
		if (!*start)
			return 1;
		else if (*str != *start)
			return 0;
}
