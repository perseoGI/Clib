// ****************************************************************************************
/**
 * @file   unit-tests.c
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

void printInt (void *node){
    int num = *(int*) node;
    printf("%d ", num);
}

LinkedList *list;

// ****************************************************************************************
// test_sendReset_transmissionError
// ****************************************************************************************
/**
 *  Check creation of linked list
 *
 * Function under testing:
 *  #create_linked_list
 *
 * Checked:
 * 	- List return pointer not null
 * 	- List is empty
 * 	- Head and tail pointers are joint and are NULL terminated on the other link
 */
// ****************************************************************************************
void test_create_linked_list(void){

    LinkedList * list = create_linked_list();

    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_INT(0, list->size);
    TEST_ASSERT_NOT_NULL(list->head);
    TEST_ASSERT_NOT_NULL(list->tail);
    TEST_ASSERT_NULL(list->head->next);
    TEST_ASSERT_NULL(list->tail->prev);
    TEST_ASSERT_EQUAL_PTR(list->head->prev, list->tail);
    TEST_ASSERT_EQUAL_PTR(list->tail->next, list->head);

    list_destroy(list);
}

// TODO cant assign pointer to null
void test_destroy_linked_list(void){
    LinkedList *list = create_linked_list();
    ListNode *head = list->head;
    ListNode *tail = list->tail;

    list_destroy(list);

    /*list = NULL;*/
    /*printf("%p\n", list);*/
    /*TEST_ASSERT_NULL(list);*/
    /*TEST_ASSERT_NULL(head);*/
    /*TEST_ASSERT_NULL(tail);*/

}


// ****************************************************************************************
// test_list_push_back
// ****************************************************************************************
/**
 *  Check push back function on sucessive calls
 *
 * Function under testing:
 *  #list_push_back
 *
 * Checked:
 * 	-
 * 	-
 */
// ****************************************************************************************
void test_list_push_back(void){
    int test_nums[] = { 0, 1, 2, 3, 4 };

    for (int i = 0; i < sizeof(test_nums)/sizeof(int); ++i){

        list_push_back(list, &test_nums[i]);

        // Check size is increasing on every push
        TEST_ASSERT_EQUAL(i + 1, list->size);
        // Check last element on the list is the element already inserted
        TEST_ASSERT_EQUAL_INT(test_nums[i], *(int*)list->tail->next->content);

    }

    // Second iteration
    ListNode *node = list->head->prev;
    int num = 0;

    // Check if node is tail node
    while (node->prev){  // Same as node != list->tail
        // Check all nodes remain on the pushed order
        TEST_ASSERT_EQUAL_INT(test_nums[num], *(int*)node->content);
        node = node->prev;
        ++num;
    }
    // Check list current size corresponds with the actual size
    TEST_ASSERT_EQUAL(num, list->size);

}


// TBD
void test_list_push_front(void){

}

void test_list_pop_back(void){

}

void test_list_pop_front(void){

}

void test_list_get_first(void){

}
void test_list_get_last(void){

}

void test_list_print(void){

}


// Needed by Unity test framework. This functions will be executed before and after each test.
void setUp(void){
    list = create_linked_list();
}

void tearDown(void){
    list_destroy(list);
}


int main (){

    UNITY_BEGIN();
    RUN_TEST(test_create_linked_list);
    RUN_TEST(test_destroy_linked_list);
    RUN_TEST(test_list_push_back);
    RUN_TEST(test_list_pop_back);
    return UNITY_END();

}
