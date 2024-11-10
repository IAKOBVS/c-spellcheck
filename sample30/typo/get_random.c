#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
gen_rand()
{
	srand(time(0));
	return rand();
}

int
main(int argc, char **argv)
{
	printf("%d\n", genrand());
	return 0;
}
