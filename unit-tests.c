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

void printInt (void *node){
    int num = *(int*) node;
    printf("%d ", num);
}



int main (){
    LinkedList * list = create_linked_list();

    /*list_print(list, printInt);*/
    int nums[] = { 0, 1, 2, 3, 4 };
    list_push_back(list, &nums[0]);
    list_push_back(list, &nums[1]);
    list_push_back(list, &nums[2]);
    list_push_back(list, &nums[3]);
    list_push_back(list, &nums[4]);

    list_print(list, printInt);

    int first = *(int*) list_pop_back(list);
    if (first == 4){
        printf("Ok\n");
    }
    else {
        printf("Error on pop back\n");
    }

    list_pop_back(list);
    list_pop_back(list);

    first = *(int*) list_pop_back(list);
    if (first == 1){
        printf("Ok\n");
    }
    else {
        printf("Error on pop back\n");
     }
    list_pop_back(list);

    // Empty list
    list_push_front(list, &nums[0]);
    list_push_front(list, &nums[1]);
    list_push_front(list, &nums[2]);
    list_push_front(list, &nums[3]);
    list_push_front(list, &nums[4]);

    first = *(int*) list_pop_front(list);
    if (first == 4){
        printf("Ok\n");
    }
    else {
        printf("Error on pop front\n");
     }
}
