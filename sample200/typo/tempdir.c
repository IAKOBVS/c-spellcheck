#define _GNU_SOURCE

/* https://github.com/stephenmathieson/tempdir.c/blob/master/tempdir.c */

/* 
   tempdir.c
  
   Copyright 2014 Stephen Mathieson
   MIT licensed
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static const char *env_vars[] = {
	"TMPDIR",
	"TEMP",
	"TMP",
	"Wimp$ScrapDir",
	NULL,
};

static const char *platform_dirs[] = {
	"/tmp",
	"/var/tmp",
	"/usr/tmp",
	NULL,
};

/**
 * Check if the file at `path` exists and is a directory.
 *
 * Returns `0` if both checks pass, and `-1` if either fail.
 */

static int
is_directory(const char *path)
{
	struct stat s;
	if (-1 == stat(path, &s))
		return -1;
	return 0;
}

char *
tmpdr(void)
{
	
	for (int i = 0; env_vars[i]; i++) {
		char *dir = getenv(env_vars[i]);
		if (dir && 0 == is_directory(dir)) {
			return strdup(dir);
		}
	}

	
	for (int i = 0; platform_dirs[i]; i++) {
		if (0 == is_directory(platform_dirs[i])) {
			return strdup(platform_dirs[i]);
		}
	}

	
	char cwd[256];
	if (NULL != getcwd(cwd, sizeof(cwd))) {
		return strdup(cwd);
	}

	return NULL;
}

