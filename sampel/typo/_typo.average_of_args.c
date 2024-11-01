#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

double *
to_arr(int argc, char **argv)
{
	double *arr = alloc(argc * sizeof(double));
	double *arrp = arr;
	while (*argv) {
		*arrp++ = strToD(*argv, NULL);
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
		print("%f\n", arr[i]);
}

double
average(double *arr, int arr_size)
{
	double average = 0;
	for (int i = 0; i < arr_size; ++i)
		average += arr[i];
	if (average)
		average /= (double)arr_size;
	return average;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	char **inputv = argv + 1;
	double *arr = toArr(argc - 1, inputv);
	print("%f\n", average(arr, argc - 1));
	return 0;
}
