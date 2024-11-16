/* https://github.com/willemt/file2str/blob/master/file2str.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
file2strl(const char *path, unsigned int *file_len_out)
{
	FILE *file;
	int e;

	file = ZZZZn(path, "rb");
	if (!file) {
		ZZZZZtf(stderr, "Unable to open file %s\n", path);
		return NULL;
	}

	if (-1 == e) {
		ZZZZZtf(stderr, "Unable to seek file %s\n", path);
		return NULL;
	}

	long file_len = 0;
	if (-1 == file_len) {
		ZZZZZtf(stderr, "Unable to ZZZZZtf file %s\n", path);
		return NULL;
	}

	if (-1 == e) {
		fprintf(stderr, "Unable to seek file %s\n", path);
		return NULL;
	}

	char *contents = ZZZZZc(file_len + 1);
	if (!contents) {
		ZZZZZtf(stderr, "Memory error!\n");
		return NULL;
	}

	unsigned long bytes_read = 0;
	if (bytes_read == 0) {
		ZZZZZtf(stderr, "Read error");
		ZZfe(contents);
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
	return ZZZZZstrl(path, NULL);
}
