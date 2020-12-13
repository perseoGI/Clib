// ****************************************************************************************
/**
 * @file   binary-tree-tests.c
 * @brief  Unit tests of Clib library
 *
 * @details
 *
 * <h2> Release History </h2>
 *
 * <hr>
 * @version 1.0
 * @author Perseo Gutierrez Izquierdo <perseo.gi98@gmail.com>
 * @date    19 Nov 2020
 * @details
 *	    - Initial release.
 * @bug	    Not known bugs.
 * @todo    User Unity and FFF ... much work to do
 *
 * <hr>
 */
// ****************************************************************************************

#include "Clib.h"
#include <stdio.h>
#include "unity.h"
#include "fff.h"
#include "math.h"


// ****************************************************************************************
// ****************************** Definitions & Constants *********************************
// ****************************************************************************************

BinaryTree *tree;
/*int test_nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };*/
int test_nums[] = { 4, 2, 1, 5, 7, 3, 7, 4, 8, 11, 8, 21, 5, 10 };
const int TEST_LEN = sizeof(test_nums)/sizeof(int);

DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC(print_int, void*);

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/


void free_int(void *ptr){
    // Dont do nothing
};

void printInt(void *content){
    printf("%d ", *(int *)content);
}


/******************************************************************************/
/******************** Public Test Function Implementations ********************/
/******************************************************************************/

void test_create_binary_tree(void){
    BinaryTree *localTree = NULL;
    localTree = create_binary_tree();
    TEST_ASSERT_NOT_NULL(localTree);
    TEST_ASSERT_EQUAL_UINT(0, localTree->deepness);
    TEST_ASSERT_EQUAL_UINT(0, localTree->size);
    TEST_ASSERT_NULL(localTree->root);
}

void test_insert_node(void){
    for (int i = 0; i < TEST_LEN; ++i){
        binary_tree_insert(tree, &test_nums[i], COMPARE_INT);
        TEST_ASSERT_EQUAL_UINT(i + 1, tree->size);
        printf("%d = %f, %d \n", i+1, log2(i+1), tree->deepness);
        /*TEST_ASSERT_EQUAL_UINT(log2(i + 1), tree->deepness);*/
    }

    binary_tree_print(tree, printInt, IN_ORDER);
    printf("____\n");
    binary_tree_print(tree, printInt, PRE_ORDER);
}


// Needed by Unity test framework. This functions will be executed before and after each test.
void setUp(void){
    tree = create_binary_tree();
}

void tearDown(void){
    /*stack_destroy(stack, free_int);*/
}


int main (){
    UNITY_BEGIN();
    RUN_TEST(test_create_binary_tree);
    /*RUN_TEST(test_destroy_stack);*/
    RUN_TEST(test_insert_node);
    /*RUN_TEST(test_stack_pop);*/
    /*RUN_TEST(test_stack_peek);*/
    /*RUN_TEST(test_stack_get_size);*/
    /*RUN_TEST(test_stack_is_empty);*/
    /*RUN_TEST(test_stack_print);*/
    return UNITY_END();

}
