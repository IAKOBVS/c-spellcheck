#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double *
to_arr(int argc, char **argv)
{
	double *arr = malloc(argc * sizeof(double));
	double *arrp = arr;
	while (*argv) {
		*arrp++ = strtod(*argv, NULL);
		++argv;
	}
	return arr;
}

int
cmp(const void *x, const void *y)
{
	if (*(double *)x == *(double *)y)
		return 0;
	if (*(double *)x > *(double *)y)
		return 1;
	return -1;
}

void
print(double *arr, int arr_size)
{
	for (int i = 0; i < arr_size; ++i)
		printf("%f\n", arr[i]);
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char **inputv = argv + 1;
	double *arr = to_arr(argc - 1, inputv);
	qsort(arr, argc - 1, sizeof(double), cmp);
	print(arr, argc - 1);
	return 0;
}
