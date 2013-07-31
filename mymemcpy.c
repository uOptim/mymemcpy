#include <stdio.h>
#include <stdint.h>
#include "mymemcpy.h"

#define VSIZE 16

typedef int v4si __attribute__ ((vector_size (VSIZE)));

typedef struct {
	char v[VSIZE];
} _v16;


__attribute__((constructor)) void __init_mymemcpy()
{
	fprintf(stderr, "MYMEMCPY IN USE!\n");
}

// alias to mymemcpy
void memcpy(void *, const void *, size_t) __attribute__((alias ("mymemcpy")));


void * mymemcpy(void *dest, const void *src, size_t n)
{
	v4si *ptr;
	char       *d = dest;
	const char *s = src;
	size_t remaining = n;

	// first bytes may not be alligned
	for (; ((uintptr_t) d % VSIZE) != 0 && remaining > 0; d++) {
		*d = *s;
		remaining--;
		s++;
	}

	v4si tmp[8];
	ptr = (void *) d;

	for (; remaining >= 8*VSIZE; ptr += 8) {
		*((_v16 *) &tmp[0]) = *(((_v16 *) s) + 0);
		*((_v16 *) &tmp[1]) = *(((_v16 *) s) + 1);
		*((_v16 *) &tmp[2]) = *(((_v16 *) s) + 2);
		*((_v16 *) &tmp[3]) = *(((_v16 *) s) + 3);
		*((_v16 *) &tmp[4]) = *(((_v16 *) s) + 4);
		*((_v16 *) &tmp[5]) = *(((_v16 *) s) + 5);
		*((_v16 *) &tmp[6]) = *(((_v16 *) s) + 6);
		*((_v16 *) &tmp[7]) = *(((_v16 *) s) + 7);
		*ptr     = tmp[0];
		*(ptr+1) = tmp[1];
		*(ptr+2) = tmp[2];
		*(ptr+3) = tmp[3];
		*(ptr+4) = tmp[4];
		*(ptr+5) = tmp[5];
		*(ptr+6) = tmp[6];
		*(ptr+7) = tmp[7];
		remaining -= 8*VSIZE;
		s += 8*VSIZE;
	}

	for (; remaining >= 4*VSIZE; ptr += 4) {
		*((_v16 *) &tmp[0]) = *(((_v16 *) s) + 0);
		*((_v16 *) &tmp[1]) = *(((_v16 *) s) + 1);
		*((_v16 *) &tmp[2]) = *(((_v16 *) s) + 2);
		*((_v16 *) &tmp[3]) = *(((_v16 *) s) + 3);
		*ptr     = tmp[0];
		*(ptr+1) = tmp[1];
		*(ptr+2) = tmp[2];
		*(ptr+3) = tmp[3];
		remaining -= 4*VSIZE;
		s += 4*VSIZE;
	}

	for (; remaining >= 2*VSIZE; ptr += 2) {
		*((_v16 *) &tmp[0]) = *(((_v16 *) s) + 0);
		*((_v16 *) &tmp[1]) = *(((_v16 *) s) + 1);
		*ptr     = tmp[0];
		*(ptr+1) = tmp[1];
		remaining -= 2*VSIZE;
		s += 2*VSIZE;
	}

	for (; remaining >= VSIZE; ptr += 1) {
		*((_v16 *) &tmp) = *((_v16 *) s);
		*ptr = tmp[0];
		remaining -= VSIZE;
		s += VSIZE;
	}

	// remaining bytes if any
	for (d = (void *) ptr; remaining > 0; d++) {
		*d = *s;
		remaining--;
		s++;
	}

	return dest;
}

