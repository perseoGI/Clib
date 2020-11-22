CC 	:= gcc
CFLAGS			:= -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-enum -Wswitch-default -Wconversion -Wunreachable-code
PROFILE_FLAGS	:= -fprofile-arcs -ftest-coverage #--whole-archive
OBJ_D 			:= obj
LIBS_I 			:= -I inc/ -I Unity/src
SRC_D 			:= src
BIN_D 			:= bin
TEST_D 			:= tests
OBJ_SRC 		:= $(OBJ_D)/$(SRC_D)
OBJ_TEST 		:= $(OBJ_D)/$(TEST_D)


TESTS_SRC 		:= $(shell find $(TEST_D) -type f -name '*.c')
#TESTS_OBJ 		:= $(TESTS_SRC:$(TEST_D)/%.c=$(OBJ_TEST)/%.o)
TESTS_OBJ 		:= $(TESTS_SRC:$(TEST_D)/%.c=$(OBJ_TEST)/%.o)

ALL_SRC 		:= $(shell find $(SRC_D) -type f -name '*.c')
ALL_OBJ 		:= $(ALL_SRC:$(SRC_D)/%.c=$(OBJ_SRC)/%.o)

# Tests
UNITY_L			:= Unity/libunity.a
CLIB_L 			:= Clib.a

#LINKED_LIST_TEST := $(OBJ_TEST)/linked-list-tests.o
LINKED_LIST_TEST := tests/linked-list-tests.c

#all: prepare $(ALL_OBJ) #lib #$(TESTS_OBJ)
all: prepare lib

lib: $(OBJ_SRC)/Clib.o
	ar rcs $(CLIB_L) $<

$(OBJ_SRC)/Clib.o: $(SRC_D)/Clib.c
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(LIBS_I) $< -c  -o $@

test:  linked-list-tests


linked-list-tests: $(CLIB_L) $(UNITY_L)
	@$(CC) -g $(PROFILE_FLAGS) $(LIBS_I) $(LINKED_LIST_TEST) -o $(BIN_D)/$@ $^
	@./$(BIN_D)/$@

#rm unit-tests.gcda unit-tests.gcno


# Update Unity Test framework submodule and generate static library
Unity/libunity.a:
	@git submodule init
	@git submodule update
	@cd Unity &&	cmake CMakeLists.txt &&	make && cd ..

prepare:
	@echo "SRC: " $(ALL_SRC)
	@echo "OBJ: " $(ALL_OBJ)
	@echo "TSRC: " $(TESTS_SRC)
	@echo "TOBJ: " $(TESTS_OBJ)
	@mkdir -p $(OBJ_SRC)
	@mkdir -p $(OBJ_TEST)
	@mkdir -p $(BIN_D)

clean:
	rm -rf $(OBJ_D) $(BIN_D)
	rm *.o *.a *.gcda *.gcov *.gcno


# This is not working yet
#$(TESTS_OBJ): $(OBJ_TEST)/%.o: $(TEST_D)/%.c:
	#@echo -e "Compiling $< -> $@"
	#$(CC) -g $(CFLAGS) $(PROFILE_FLAGS) -I Unity/src -c -o $@ $<

#$(ALL_OBJ): $(OBJ_SRC)/%.o: $(SRC_D)/%.c:
	#@echo -e "Compiling $< -> $@"
	#cc -g $(CFLAGS) $(PROFILE_FLAGS) -I $(INC_D) -I Unity/src -c -o $@ $<
