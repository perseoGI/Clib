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
 * @date    10 Jan 2021
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

#define TEST_POS 0
#define IN_POS 1
#define PRE_POS 2
#define POST_POS 3


BinaryTree *tree;
/*int test_nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };*/
int test_nums[] = { 4, 2, 1, 5, 7, 3, 8, 11, 21, 10 };
/*int test_nums[] = { 4, 2, 1, 5, 12, 21, 4, 7, 3, 6, 6, 8, 11, 10 };*/

int test_nums_order[4][10] = {
    {4, 2, 1, 5, 7, 3, 8, 11, 21, 10 },
    {1, 2, 3, 4, 5, 7, 8, 10, 11, 21},   // IN
    {4, 2, 1, 3, 5, 7, 8, 11, 10, 21},   // PRE
    {1, 3, 2, 10, 21, 11, 8, 7, 5, 4},   // POST
};


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
        /*printf("%d = %f, %d \n", i+1, log2(i+1), tree->deepness);*/
        /*TEST_ASSERT_EQUAL_UINT(log2(i + 1), tree->deepness);*/
        // TODO check deepness
    }

    binary_tree_print(tree, printInt);
}

void test_destroy_binary_tree(void){
    binary_tree_destroy(tree, free_int);
    // TODO check structure free
}

void test_traversal(void){
    for (int i = 0; i < TEST_LEN; ++i){
        binary_tree_insert(tree, &test_nums_order[TEST_POS][i], COMPARE_INT);
    }
    LinkedList *in_order = binary_tree_traversal(tree, IN_ORDER);

    for (unsigned int i = 0; i < 10; ++i){
        int expectedValue = *(int*)list_get_element(in_order, i) ;
        TEST_ASSERT_EQUAL_INT(test_nums_order[IN_POS][i], expectedValue);
    }
    list_destroy(in_order);

    LinkedList *pre_order = binary_tree_traversal(tree, PRE_ORDER);

    for (unsigned int i = 0; i < 10; ++i){
        int expectedValue = *(int*)list_get_element(pre_order, i) ;
        TEST_ASSERT_EQUAL_INT(test_nums_order[PRE_POS][i], expectedValue);
    }
    list_destroy(pre_order);

    LinkedList *post_order = binary_tree_traversal(tree, PRE_ORDER);

    for (unsigned int i = 0; i < 10; ++i){
        int expectedValue = *(int*)list_get_element(post_order, i) ;
        TEST_ASSERT_EQUAL_INT(test_nums_order[POST_ORDER][i], expectedValue);
    }
    list_destroy(post_order);
}


void test_traversal_print (void){
    for (int i = 0; i < TEST_LEN; ++i){
        binary_tree_insert(tree, &test_nums_order[TEST_POS][i], COMPARE_INT);
    }

    printf("\n_________IN_____________\n");
    binary_tree_traversal_print(tree, printInt, IN_ORDER);
    printf("\n_________PRE_____________\n");
    binary_tree_traversal_print(tree, printInt, PRE_ORDER);
    printf("\n_________POST_____________\n");
    binary_tree_traversal_print(tree, printInt, POST_ORDER);
    printf("\n______________________\n");

}


// Needed by Unity test framework. This functions will be executed before and after each test.
void setUp(void){
    tree = create_binary_tree();
}

void tearDown(void){
    binary_tree_destroy(tree, free_int);
}


int main (){
    UNITY_BEGIN();
    RUN_TEST(test_create_binary_tree);
    RUN_TEST(test_destroy_binary_tree);
    RUN_TEST(test_insert_node);
    RUN_TEST(test_traversal);
    RUN_TEST(test_traversal_print);
    return UNITY_END();

}
