all: Clib.o
	ar rcs Clib.a $<

Clib.o:	Clib.h Clib.c
	gcc -c Clib.c

test: Clib.a
	gcc -g unit-tests.c $< -o $@
#	./$@

clean:
	rm *.o *.a
