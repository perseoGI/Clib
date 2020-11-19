all: Clib.o
	ar rcs Clib.a $<

Clib.o:	Clib.h Clib.c
	gcc -c Clib.c

test: Clib.a Unity/libunity.a
	gcc -g $^ unit-tests.c -I Unity/src -o $@
	./$@


# Update Unity Test framework submodule and generate static library
Unity/libunity.a:
	git submodule init
	git submodule update
	cd Unity &&	cmake CMakeLists.txt &&	make
	cd ..


clean:
	rm *.o *.a test

