// ****************************************************************************************
/**
 * @file   linked-list-tests.c
 * @brief  Unit tests of linked list structure
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
LinkedList *list;
int test_nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/
void printInt (void *node){
    int num = *(int*) node;
    printf("%d ", num);
}


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
 * Check:
 * 	- Size increase whith every push
 * 	- New element is inserted at the end of list
 * 	- List remain consistant over every push
 */
// ****************************************************************************************
void test_list_push_back(void){

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


// ****************************************************************************************
// test_list_push_front
// ****************************************************************************************
/**
 *  Check push front function on sucessive calls
 *
 * Function under testing:
 *  #list_push_front
 *
 * Check:
 * 	- Size increase whith every push
 * 	- New element is inserted on the beginning of list
 * 	- List remain consistant over every push
 */
// ****************************************************************************************
void test_list_push_front(void){

    for (int i = 0; i < sizeof(test_nums)/sizeof(int); ++i){
        list_push_front(list, &test_nums[i]);

        // Check size is increasing on every push
        TEST_ASSERT_EQUAL(i + 1, list->size);
        // Check last element on the list is the element already inserted
        TEST_ASSERT_EQUAL_INT(test_nums[i], *(int*)list->head->prev->content);

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


// ****************************************************************************************
// test_list_pop_back
// ****************************************************************************************
/**
 *  Check pop back function on sucessive calls
 *
 * Function under testing:
 *  #list_pop_back
 *
 * Check:
 * 	- Size decrease whith every pop
 * 	- Element popped corresponds, in order with element pushed
 */
// ****************************************************************************************
void test_list_pop_back(void){
    int size = sizeof(test_nums)/sizeof(int);
    int value;

    // Generate a list appending all elements in inverse order
    for (int i = 0; i < size; ++i){
        list_push_front(list, &test_nums[i]);
    }

    for (int i = 0; i < size; ++i){
        // Obtain elements in order
        value = *(int*)list_pop_back(list);
        // Check popped value is correct
        TEST_ASSERT_EQUAL_INT(test_nums[i], value);
        // Check list size decrease on every pop
        TEST_ASSERT_EQUAL(size - i - 1, list->size);
    }

}


// ****************************************************************************************
// test_list_pop_front
// ****************************************************************************************
/**
 *  Check pop front function on sucessive calls
 *
 * Function under testing:
 *  #list_pop_front
 *
 * Check:
 * 	- Size decrease whith every pop
 * 	- Element popped corresponds, in order with element pushed
 */
// ****************************************************************************************
void test_list_pop_front(void){
    int size = sizeof(test_nums)/sizeof(int);
    int value;

    // Generate a list appending all elements in order
    for (int i = 0; i < size; ++i){
        list_push_back(list, &test_nums[i]);
    }

    for (int i = 0; i < size; ++i){
        // Obtain elements in order
        value = *(int*)list_pop_front(list);
        // Check popped value is correct
        TEST_ASSERT_EQUAL_INT(test_nums[i], value);
        // Check list size decrease on every pop
        TEST_ASSERT_EQUAL(size - i - 1, list->size);
    }
}


// ****************************************************************************************
// test_list_get_first
// ****************************************************************************************
/**
 *  Check get first function
 *
 * Function under testing:
 *  #list_get_first
 *
 * Check:
 * 	- Returns NULL when list is empty
 * 	- First element of list always remains constant with changes on the back
 */
// ****************************************************************************************
void test_list_get_first(void){
    int value;

    // Check return of NULL when list is empty
    TEST_ASSERT_NULL(list_get_first(list));

    for (int i = 0; i < sizeof(test_nums)/sizeof(int); ++i){
        // Populate list
        list_push_back(list, &test_nums[i]);
        // Obtain first element
        value = *(int*)list_get_first(list);
        // Check first element of list remains inmutable
        TEST_ASSERT_EQUAL_INT(test_nums[0], value);
    }

}


// ****************************************************************************************
// test_list_get_last
// ****************************************************************************************
/**
 *  Check get last function
 *
 * Function under testing:
 *  #list_get_last
 *
 * Check:
 * 	- Returns NULL when list is empty
 * 	- Last element of list always corresponds with last element pushed on the back
 */
// ****************************************************************************************
void test_list_get_last(void){
    int value;
    int size = sizeof(test_nums)/sizeof(int);

    // Check return of NULL when list is empty
    TEST_ASSERT_NULL(list_get_last(list));

    for (int i = 0; i < size; ++i){
        // Populate list
        list_push_back(list, &test_nums[i]);
        // Obtain first element
        value = *(int*)list_get_last(list);
        // Check first element of list remains inmutable
        TEST_ASSERT_EQUAL_INT(test_nums[i], value);
    }
}

void test_list_print(void){
    // TODO
}


// ****************************************************************************************
// test_list_get_element
// ****************************************************************************************
/**
 *  Check get element function
 *
 * Function under testing:
 *  #list_get_element
 *
 * Check:
 * 	- Returns NULL when list is empty
 * 	- Element on Nth position is correct
 */
// ****************************************************************************************
void test_list_get_element(void){
    int value;
    int size = sizeof(test_nums)/sizeof(int);

    for (int i = 0; i < size; ++i){
        // Check return of NULL when list is empty
        TEST_ASSERT_NULL(list_get_element(list, i));
    }

    for (int i = 0; i < size; ++i){
        // Populate list
        list_push_back(list, &test_nums[i]);
    }
    for (int i = 0; i < size; ++i){
        // Obtain elements
        value = *(int*)list_get_element(list, i);
        // Check first element of list remains inmutable
        TEST_ASSERT_EQUAL_INT(test_nums[i], value);
    }
}


// ****************************************************************************************
// test_list_find_node
// ****************************************************************************************
/**
 *  Check get element function
 *
 * Function under testing:
 *  #list_get_element
 *
 * Check:
 * 	- Returns NULL when list is empty
 * 	- Element on Nth position is correct
 */
// ****************************************************************************************
void test_list_find_node(void){
    int value;
    int size = sizeof(test_nums)/sizeof(int);


    for (int i = 0; i < size; ++i){
        // Populate list
        list_push_back(list, &test_nums[i]);
    }

    for (int i = 0; i < size; ++i){
        ListNode *node = list_find_node(list, &test_nums[i], COMPARE_INT);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *(int*)node->content);
    }
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
    RUN_TEST(test_list_pop_front);
    RUN_TEST(test_list_get_first);
    RUN_TEST(test_list_get_last);

    RUN_TEST(test_list_get_element);
    RUN_TEST(test_list_find_node);
    return UNITY_END();

}
