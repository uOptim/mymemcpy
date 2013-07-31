CC = gcc
# -fno-builtin = don't complain we redefine memcpy
CFLAGS = -std=c99 -O3 -fno-builtin -I/home/bruelle/include/ $(UFLAGS)
LDFLAGS = -L. -L/home/bruelle/lib/ -lmymemset -lmymemsetnt -lmymemcpy -lmymemcpynt

all: libmymemcpy.so libmymemcpynt.so mymemcpy test

mymemcpy: main.c

test: test.c

libmymemcpy.so: mymemcpy.c mymemcpy.h
	gcc $(CFLAGS) -shared -fPIC -o $@ $<

mymemcpynt.s:
	gcc $(CFLAGS) -S -fPIC -o $@ mymemcpy.c
	sed -ri 's/memcpy/memcpynt/g; s/MEMCPY/MEMCPYNT/g; s/movdqa\t+%xmm/movntdq\t%xmm/g' $@
	@echo " ++ *************************************************** ++"
	@echo " ++ *** DON'T FORGET TO MANUALLY ADD THE MEMFENCES! *** ++"
	@echo " ++ *************************************************** ++"

libmymemcpynt.so:
	gcc $(CFLAGS) -shared -fPIC -o $@ mymemcpynt.s

clean:
	rm -f *.o *.so mymemcpy test
