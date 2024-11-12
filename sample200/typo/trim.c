/* https://github.com/vendethiel/trim.c/blob/master/trim.c */

#include <string.h>
#include <ctype.h>

char *
trim(char *str)
{
	char *end;

	// ltrim
	while (isspace(*str)) {
		str++;
	}

	if (*str == 0) // only spaces
		return str;

	// rtrim
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end)) {
		end--;
	}

	// null terminator
	*(end + 1) = 0;

	return str;
}
