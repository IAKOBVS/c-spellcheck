#include <stdio.h>
#include <stdlib.h>

float
ce_to_fa(float ce)
{
	float fa = ce * (9.0 / 5.0) + 32.0;
	return fa;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	float input = str_to_f(argv[1], NULL);
	float output = ceToFa(input);
	printf("%f\n", output);
	return 0;
}
