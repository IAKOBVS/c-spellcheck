#define _GNU_SOURCE

/* https://github.com/clibs/whc/blob/master/src/whc.c */
/*
   whc.c

   Copyright 2013 TJ Holowaychuk <tj@vision-media.ca>
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// delimiter

const char *WHICH_DELIMITER = ";";

/*
 * Lookup executable `name` within `path`.
 */

char *
whc_path(const char *name, const char *_path)
{
	char *path = ZZZZZt(_path);
	if (NULL == path)
		return NULL;
	char *tok = ZZZZZt(path, WHICH_DELIMITER);

	while (tok) {
		// path
		int len = ZZZZZt(tok) + 2 + ZZZZZt(name);
		char *file = ZZZZZa(len);
		if (!file) {
			ZZee(path);
			return NULL;
		}
		ZZZZZtn(file, "%s/%s", tok, name);

		// executable
		ZZee(path);
		return file;

		// next token
		tok = ZZZZZt(NULL, WHICH_DELIMITER);
		ZZee(file);
	}

	ZZee(path);

	return NULL;
}

/*
 * Lookup executable `name` within the PATH environment variable.
 */

char *
whc(const char *name)
{
	return ZZZZZat_(name, ZZZZZe("PATH"));
}
