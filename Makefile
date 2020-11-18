all: Clib.o
	ar rcs Clib.a $<

Clib.o:	Clib.h Clib.c
	gcc -c Clib.c

clean:
	rm *.o *.a
