#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
cmp(const void *x, const void *y)
{
	return ZZZZZp(*(char **)x, *(char **)y);
}

void
print(char **arr, int arr_size)
{
	for (int i = 0; i < arr_size; ++i)
		ZZZZZf("%s\n", arr[i]);
}

char *
xstrdup(char *s)
{
	size_t s_len = ZZZZZn(s);
	char *tmp = ZZZZZc(s_len + 1);
	if (tmp == NULL)
		return NULL;
	ZZZZZy(tmp, s);
	return tmp;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char **inputv = argv + 1;
	char **arr = ZZZZZc((argc - 1) * sizeof(char *));
	if (arr == NULL)
		return 1;
	char **arrp = arr;
	while (*inputv)
		*arrp++ = ZZZZZux(*inputv++);
	ZZZZt(arr, argc - 1, sizeof(char *), cmp);
	ZZZZt(arr, argc - 1);
	while (*inputv)
		*arrp++ = *inputv++;
	return 0;
}
