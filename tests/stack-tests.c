// ****************************************************************************************
/**
 * @file   hast-map-tests.c
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


// ****************************************************************************************
// ****************************** Definitions & Constants *********************************
// ****************************************************************************************
Stack *stack;
int test_nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
const int TEST_LEN = sizeof(test_nums)/sizeof(int);

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/


void free_int(void *ptr){
    // Dont do nothing
};

/******************************************************************************/
/******************** Public Test Function Implementations ********************/
/******************************************************************************/

// ****************************************************************************************
// test_sendReset_transmissionError
// ****************************************************************************************
/**
 *  Check creation of linked list
 *
 * Function under testing:
 *  #create_linked_list
 *
 * Check:
 * 	- List return pointer not null
 * 	- List is empty
 * 	- Head and tail pointers are joint and are NULL terminated on the other link
 */
// ****************************************************************************************
void test_create_stack(void){
    Stack *local_stack = create_stack();
    TEST_ASSERT_NOT_NULL(local_stack);
    TEST_ASSERT_EQUAL_UINT(0, local_stack->size);
    TEST_ASSERT_NULL(local_stack->top);
}


void test_destroy_stack(void){
    Stack *local_stack = create_stack();
    stack_destroy(local_stack, free_int);

    // TODO check structure free

}


void test_stack_push(void){
    SingleNode *node;

    for (int i = 0; i < TEST_LEN; ++i){
        stack_push(stack, &test_nums[i]);
        TEST_ASSERT_NOT_NULL(stack->top);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *(int*)stack->top->content);
    }

    node = stack->top;
    for (int i = TEST_LEN - 1; i >= 0; --i){
        TEST_ASSERT_NOT_NULL(node->content);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *(int*)node->content);
        node = node->next;
    }
}


void test_stack_pop(void){
    int *value;
    TEST_ASSERT_NULL(stack_pop(stack));

    for (int i = 0; i < TEST_LEN; ++i){
        stack_push(stack, &test_nums[i]);
    }

    for (int i = TEST_LEN - 1; i >= 0; --i){
        value = stack_pop(stack);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *(int*)value);
    }
}

void test_stack_peek(void){
    SingleNode *node;
    int *value;
    for (int i = 0; i < TEST_LEN; ++i){
        stack_push(stack, &test_nums[i]);
        value = stack_peek(stack);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *(int*)value);
        TEST_ASSERT_EQUAL_UINT(i + 1, stack->size);         // Check stack size has not decreased
    }

    node = stack->top;
    // Check all stack remains the same
    for (int i = TEST_LEN - 1; i >= 0; --i){
        TEST_ASSERT_NOT_NULL(node->content);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *(int*)node->content);
        node = node->next;
    }
}

void test_stack_get_size(void){
    unsigned int size;
    for (int i = 0; i < TEST_LEN; ++i){
        stack_push(stack, &test_nums[i]);
        size = stack_get_size(stack);
        TEST_ASSERT_EQUAL_UINT(i + 1, size);
    }
}


void test_stack_is_empty(void){
    TEST_ASSERT_TRUE(stack_is_empty(stack));
    for (int i = 0; i < TEST_LEN; ++i){
        stack_push(stack, &test_nums[i]);
        TEST_ASSERT_FALSE(stack_is_empty(stack));
    }
}


// Needed by Unity test framework. This functions will be executed before and after each test.
void setUp(void){
    stack = create_stack();
}

void tearDown(void){
    stack_destroy(stack, free_int);
}


int main (){
    UNITY_BEGIN();
    RUN_TEST(test_create_stack);
    RUN_TEST(test_destroy_stack);
    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_peek);
    RUN_TEST(test_stack_get_size);
    RUN_TEST(test_stack_is_empty);
    return UNITY_END();

}
