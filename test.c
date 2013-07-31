#include "mymemcpy.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define SIZE 7018911
#define OFFSET 7 // test alignment

int main(void)
{
	char *c = malloc(SIZE);
	char *d = malloc(SIZE);

	for (int i = 0; i < SIZE; i++) {
		d[i] = 'a' + i;
	}

#ifdef NT
	mymemcpynt(c+OFFSET, d+OFFSET, SIZE-OFFSET);
#else
	mymemcpy(c+OFFSET, d+OFFSET, SIZE-OFFSET);
#endif

	for (int i = OFFSET; i < SIZE; i++) {
		assert(c[i] == d[i]);
	}

	puts("OK");
	free(c);
	free(d);

	return 0;
}
