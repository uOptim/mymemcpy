#define _GNU_SOURCE
#include "mymemset.h"
#include "mymemcpy.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define COUNT 4

#define timediff_ts(s,e) \
	(1000000000*(e.tv_sec - s.tv_sec) + (e.tv_nsec - s.tv_nsec))


void clflush_buff(char *buff, size_t size)
{
	for (int i = 0; i < size; i += 32) {
		__asm__ __volatile__("clflush (%%rax);":: "a" (&buff[i]));
	}
}


int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <buf size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *buf[2];
	size_t size = atoi(argv[1]) * 1024;

	buf[0] = mmap(
		NULL, size,
		PROT_READ | PROT_WRITE,
		//MAP_SHARED | MAP_ANONYMOUS,
		//MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB,
		MAP_PRIVATE | MAP_ANONYMOUS,
		0, 0
	);
	
	buf[1] = mmap(
		NULL, size,
		PROT_READ | PROT_WRITE,
		//MAP_SHARED | MAP_ANONYMOUS,
		//MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB,
		MAP_PRIVATE | MAP_ANONYMOUS,
		0, 0
	);

	mymemset(buf[0], 1, size);
	mymemset(buf[1], 1, size);

	double times[COUNT];
	struct timespec start, end;
	for (int n = 0; n < COUNT; n++) {
		clflush_buff(buf[0], size);
		clflush_buff(buf[1], size);

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
#ifdef NT
		mymemcpynt(buf[0], buf[1], size);
#else
		mymemcpy(buf[0], buf[1], size);
#endif
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

		times[n] = ((double) timediff_ts(start, end));
	}

	double timeS;
	double sizeGB = (double)size / 1024 / 1024 / 1024;
	printf("%zd", size/1024);
	for (int n = 0; n < COUNT; n++) {
		timeS = times[n] / 1000 / 1000 / 1000;
		printf(" %g", sizeGB/timeS);
	}

	exit(EXIT_SUCCESS);
}
