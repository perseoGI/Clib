CC 				:= gcc
CFLAGS			:= -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-enum -Wswitch-default -Wconversion -Wunreachable-code
PROFILE_FLAGS	:= -fprofile-arcs -ftest-coverage
SRC_D 			?= src
OBJ_D 			?= obj
TEST_D 			:= tests
BIN_D 			:= bin
OBJ_SRC 		:= $(OBJ_D)/$(SRC_D)
OBJ_TEST 		:= $(OBJ_D)/$(TEST_D)

LIBS_I 			:= -I inc/ -I Unity/src


ALL_SRC 		:= $(shell find $(SRC_D) -type f -name '*.c')
ALL_OBJ 		:= $(ALL_SRC:$(SRC_D)/%.c=$(OBJ_SRC)/%.o)

TESTS_SRC 		:= $(shell find $(TEST_D) -type f -name '*.c')
TESTS_OBJ 		:= $(TESTS_SRC:$(TEST_D)/%.c=$(OBJ_TEST)/%.o)
TESTS_BIN 		:= $(TESTS_SRC:$(TEST_D)/%.c=$(BIN_D)/%.out)

# Project libraries
UNITY_L			:= Unity/libunity.a
CLIB_L 			:= Clib.a
FFF_I 			:= -I fff/

# Tests objects
LINKED_LIST_TEST := $(OBJ_TEST)/linked-list-tests.o
HASH_MAP_TEST 	 := $(OBJ_TEST)/hash-map-tests.o
STACK_TEST 	 	 := $(OBJ_TEST)/stack-tests.o


all: prepare clib

clib: $(ALL_OBJ)
	ar rcs $(CLIB_L) $^

$(OBJ_D)/%.o: %.c
	@echo -e "Compiling $< -> $@"
	$(CC) -g $(CFLAGS) $(PROFILE_FLAGS) $(LIBS_I) $(FFF_I) -c $< -o $@


test: $(TEST_OBJ) sync_submodules linked-list-tests hash-map-tests stack-tests


linked-list-tests: $(LINKED_LIST_TEST) $(CLIB_L) $(UNITY_L)
	@$(CC) -g $(PROFILE_FLAGS) $(LIBS_I) -o $(BIN_D)/$@ $^
	@./$(BIN_D)/$@

hash-map-tests: $(HASH_MAP_TEST) $(CLIB_L) $(UNITY_L)
	@$(CC) -g $(PROFILE_FLAGS) $(LIBS_I) -o $(BIN_D)/$@ $^
	@./$(BIN_D)/$@

stack-tests: $(STACK_TEST) $(CLIB_L) $(UNITY_L)
	@$(CC) -g $(PROFILE_FLAGS) $(LIBS_I) -o $(BIN_D)/$@ $^
	@./$(BIN_D)/$@
#rm unit-tests.gcda unit-tests.gcno

sync_submodules:
	@git submodule init
	@git submodule update

# Update Unity Test framework submodule and generate static library
Unity/libunity.a:
	@git submodule init
	@git submodule update
	@cd Unity &&	cmake CMakeLists.txt &&	make && cd ..

prepare:
	@echo "tests" $(TESTS_BIN)
	@mkdir -p $(OBJ_SRC)
	@mkdir -p $(OBJ_TEST)
	@mkdir -p $(BIN_D)

clean:
	rm -rf $(OBJ_D) $(BIN_D)
	rm *.o *.a *.gcda *.gcov *.gcno


# Not working yet
#tests: $(TEST_OBJ) $(TESTS_BIN)
#$(BIN_D)/%.out: %.o
	#@echo -e "Generating test $< -> $@"
	#@$(CC) -g $(PROFILE_FLAGS) $(LIBS_I) $< -o $(BIN_D)/$@ $(CLIB_L) $(UNITY_L)
