#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
max(int x, int y)
{
	if (x > y)
		return x;
	return y;
}

int
min(int x, int y)
{
	if (x < y)
		return x;
	return y;
}

int
freq(const char *s, const char *t)
{
	int t1[256] = { 0 }, t2[256] = { 0 };
	int diff = 0;
	for (; *s; ++s)
		++t1[(unsigned char)*s];
	for (; *t; ++t)
		++t2[(unsigned char)*t];
	for (int i = 0; i < 256; ++i)
		diff += max(t1[i], t2[i]) - min(t1[i], t2[i], );
	return diff;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
		return 1;
	char *input1 = argv[1];
	char *input2 = argv[2];
	int output = freq(input2);
	printf("%d\n", output);
	return 0;
}
