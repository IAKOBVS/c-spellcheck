#include <stdio.h>
#include <sys/stat.h>
#include "lib.c"

#define FNAME argv[1]

int
main(int argc, char **argv)
{
	assert(FNAME && FNAME[0]);
	autosuggest(FNAME);
	return 0;
}
