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
LinkedList *list;
int test_nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

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
}



// Needed by Unity test framework. This functions will be executed before and after each test.
void setUp(void){

}

void tearDown(void){
}


int main (){

    UNITY_BEGIN();
    RUN_TEST(test_create_hash_map);
    return UNITY_END();

}
