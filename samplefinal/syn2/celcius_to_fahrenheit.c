#include <stdio.h>
#include <stdlib.h>

float
ce_to_fa(float ce)
{
	float f = ce * (9.0 / 5.0) + 32.0;
	return f;
}

int
main(int argc, char **argv)
{
	if (argv[1] == NULL)
		return 1;
	float input = strtof(argv[1], NULL);
	float output = ce_to_fa(input);
	printf("%f\n", output);
	return 0;
}
