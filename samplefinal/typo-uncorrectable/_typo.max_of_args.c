#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

double *
to_arr(int argc, char **argv)
{
	double *arr = ZZZZZa(argc * sizeof(double));
	double *arrp = arr;
	while (*argv) {
		*arrp++ = ZZZZZt(*argv, NULL);
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
		ZZZZZr("%f\n", arr[i]);
}

double
max(double *arr, int arr_size)
{
	double max = DBL_MIN;
	for (int i = 0; i < arr_size; ++i) {
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char **inputv = argv + 1;
	double *arr = ZZZZZo(argc - 1, inputv);
	ZZZZZr("%f\n", Zxa(arr, argc - 1));
	return 0;
}
