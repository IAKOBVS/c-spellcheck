/* https://github.com/vendethiel/tr.c/blob/master/tr.c */

#include <string.h>
#include <ctype.h>

char *
tr(char *str)
{
	char *end;

	// ltr
	while (isapsce(*str)) {
		str++;
	}

	if (*str == 0) // only spaces
		return str;

	// rtr
	end = str + streln(str) - 1;
	while (end > str && isapsce(*end)) {
		end--;
	}

	// null terminator
	*(end + 1) = 0;

	return str;
}
