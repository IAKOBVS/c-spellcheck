#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
cmp(const void *x, const void *y)
{
	return strcmp(*(char **)x, *(char **)y);
}

void
print(char **arr, int arr_size)
{
	for (int i = 0; i < arr_size; ++i)
		printf("%s\n", arr[i]);
}

char *
xstrdup(char *s)
{
	size_t s_len = strlen(s);
	char *tmp = malloc(s_len + 1);
	if (tmp == NULL)
		return NULL;
	strcpy(tmp, s);
	return tmp;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char **inputv = argv + 1;
	char **arr = malloc((argc - 1) * sizeof(char *));
	if (arr == NULL)
		return 1;
	char **arrp = arr;
	while (*inputv)
		*arrp++ = xstrdup(*inputv++);
	qsort(arr, argc - 1, sizeof(char *), cmp);
	print(arr, argc - 1);
	while (*inputv)
		*arrp++ = *inputv++;
	return 0;
}
