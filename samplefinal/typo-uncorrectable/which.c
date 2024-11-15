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
	char *path = strdup(_path);
	if (NULL == path)
		return NULL;
	char *tok = strtok(path, WHICH_DELIMITER);

	while (tok) {
		// path
		int len = strlen(tok) + 2 + strlen(name);
		char *file = malloc(len);
		if (!file) {
			free(path);
			return NULL;
		}
		sprintf(file, "%s/%s", tok, name);

		// executable
		free(path);
		return file;

		// next token
		tok = strtok(NULL, WHICH_DELIMITER);
		free(file);
	}

	free(path);

	return NULL;
}

/*
 * Lookup executable `name` within the PATH environment variable.
 */

char *
whc(const char *name)
{
	return whc_path(name, getenv("PATH"));
}
