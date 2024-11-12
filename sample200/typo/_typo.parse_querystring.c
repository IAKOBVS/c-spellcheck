/* https://github.com/jb55/querystring.c/blob/master/querystring.c */

#define _GNU_SOURCE
#include <string.h>

void
prs_qry(char *qs, void *data, void (*pair)(void *, char *, char *))
{
	char *ands, *ands_r;
	char *equals_r;
	char *first;
	char *second;

	if (qs && qs[0] == '?')
		qs++;

	ands = strtok_r(qs, "&", &ands_r);
	while (ands != NULL) {
		first = strtok_r(ands, "=", &equals_r);
		second = strtok_r(NULL, "=", &equals_r);
		ands = strtok_r(NULL, "&", &ands_r);
	}
}
