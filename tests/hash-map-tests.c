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
HashMap *map;
int test_nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
const int TEST_LEN = sizeof(test_nums)/sizeof(int);

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/


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
void test_create_hash_map(void){
    HashMap *map = create_hash_map(5);
}

void test_hash_map_set(void){
    char key_buff[10];
    int *value;
    for (int i = 0; i < TEST_LEN; ++i){
        sprintf(key_buff, "%d", test_nums[i]);
        hash_map_set(map, key_buff, &test_nums[i]);
    }
    for (int i = 0; i < TEST_LEN; ++i){
        sprintf(key_buff, "%d", test_nums[i]);
        value = hash_map_get(map, key_buff);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *value);
    }
}

// Improve test because this is the same for set
void test_hash_map_get(void){
    char key_buff[10];
    int *value;
    for (int i = 0; i < TEST_LEN; ++i){
        sprintf(key_buff, "%d", test_nums[i]);
        hash_map_set(map, key_buff, &test_nums[i]);
    }
    for (int i = 0; i < TEST_LEN; ++i){
        sprintf(key_buff, "%d", test_nums[i]);
        value = hash_map_get(map, key_buff);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *value);
    }
}

void test_hash_map_pop(void){
    char key_buff[10];
    int *value;
    for (int i = 0; i < TEST_LEN; ++i){
        sprintf(key_buff, "%d", test_nums[i]);
        hash_map_set(map, key_buff, &test_nums[i]);
    }
    for (int i = 0; i < TEST_LEN; ++i){
        sprintf(key_buff, "%d", test_nums[i]);
        value = hash_map_pop(map, key_buff);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *value);
        value = hash_map_pop(map, key_buff);
        TEST_ASSERT_NULL(value);
    }
}

void free_int(void *ptr){
    // Dont do nothing
};

void test_hash_map_remove(void){
    char key_buff[10];
    int *value;
    for (int i = 0; i < TEST_LEN; ++i){
        sprintf(key_buff, "%d", test_nums[i]);
        hash_map_set(map, key_buff, &test_nums[i]);
    }
    for (int i = 0; i < TEST_LEN; ++i){
        sprintf(key_buff, "%d", test_nums[i]);
        value = hash_map_remove(map, key_buff, free_int);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT(test_nums[i], *value);
        value = hash_map_remove(map, key_buff, free_int);
        TEST_ASSERT_NULL(value);
    }
}

// Needed by Unity test framework. This functions will be executed before and after each test.
void setUp(void){
    map = create_hash_map(5);
}

void tearDown(void){
}


int main (){

    UNITY_BEGIN();
    RUN_TEST(test_create_hash_map);
    RUN_TEST(test_hash_map_set);
    /*RUN_TEST(test_hash_map_get);*/
    RUN_TEST(test_hash_map_pop);
    /*RUN_TEST(test_hash_map_remove);*/
    return UNITY_END();

}
