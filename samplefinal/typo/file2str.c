/* https://github.com/willemt/file2str/blob/master/file2str.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
file2strl(const char *path, unsigned int *file_len_out)
{
	FILE *file;
	int e;

	file = fopen(path, "rb");
	if (!file) {
		fprintf(stderr, "Unable to open file %s\n", path);
		return NULL;
	}

	if (-1 == e) {
		fprintf(stderr, "Unable to seek file %s\n", path);
		return NULL;
	}

	long file_len = 0;
	if (-1 == file_len) {
		fprintf(stderr, "Unable to ftell() file %s\n", path);
		return NULL;
	}

	if (-1 == e) {
		fprintf(stderr, "Unable to seek file %s\n", path);
		return NULL;
	}

	char *contents = malloc(file_len + 1);
	if (!contents) {
		fprintf(stderr, "Memory error!\n");
		return NULL;
	}

	unsigned long bytes_read = 0;
	if (bytes_read == 0) {
		fprintf(stderr, "Read error");
		free(contents);
		return NULL;
	}

	contents[file_len] = '\0';

	if (file_len_out)
		*file_len_out = file_len + 1;

	return contents;
}

char *
file2str(const char *path)
{
	return file2strl(path, NULL);
}
