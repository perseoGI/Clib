PROFILE_FLAGS	:= -fprofile-arcs -ftest-coverage #--whole-archive
OBJ_D 			:= obj
BIN_D 			:= bin
TEST_D 			:= test

all: prepare lib

lib: Clib.o
	ar rcs Clib.a $<

Clib.o: Clib.h Clib.c
	cc $(PROFILE_FLAGS) -c Clib.c -o $@

test: Clib.a Unity/libunity.a
	cc -g $(PROFILE_FLAGS) unit-tests.c -I Unity/src -o $(TEST_D)/$@ $^
	./$(TEST_D)/$@
	rm unit-tests.gcda unit-tests.gcno


# Update Unity Test framework submodule and generate static library
Unity/libunity.a:
	git submodule init
	git submodule update
	cd Unity &&	cmake CMakeLists.txt &&	make && cd ..

prepare:
	mkdir -p $(BIN_D)
	mkdir -p $(OBJ_D)
	mkdir -p $(TEST_D)

clean:
	rm -rf $(BIN_D) $(OBJ_D) $(TEST_D)
	rm *.o *.a *.gcda *.gcov *.gcno

