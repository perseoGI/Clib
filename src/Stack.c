// ****************************************************************************************
/**
 * @file   Stack.c
 * @brief  Implementation of Stack data structure on C
 *
 * @details This source file includes a Stackk implementation.
 *
 * <h2> Release History </h2>
 *
 * <hr>
 * @version 1.1
 * @author Perseo Gutierrez Izquierdo <perseo.gi98@gmail.com>
 * @date    18 Nov 2020
 * @details
 *	    - Initial release.
 * @bug	    Not known bugs.
 * @todo    Make unit tests
 *
 * <hr>
 */
// ****************************************************************************************

// ****************************************************************************************
// ********************************** Include Files ***************************************
// ****************************************************************************************
#include "Clib.h"

//=======================================================================================//
//                                                                                       //
//                                     Stack API                                         //
//                                                                                       //
//=======================================================================================//

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/


/******************************************************************************/
/*********************** Public Functions Implementations *********************/
/******************************************************************************/

// ****************************************************************************************
// create_stack
// ****************************************************************************************
/**
 *  Initialice stack structure
 * @param[in]    none
 * @param[out]   none
 * @return       valid pointer to stack structure
 */
// ****************************************************************************************
Stack * create_stack(void) {

    Stack *s = malloc(sizeof(Stack));
    s->size = 0;
    s->top = NULL;
    return s;
}


// ****************************************************************************************
// stack_push
// ****************************************************************************************
/**
 *  Insert #value on the top of the #stack
 * @param[in]    stack Stack to insert #value
 * @param[in]    value Pointer to data to be stored on the first position of stack
 * @param[out]   none
 * @return       none
 *
 * @details
 *
 * Stack initial state:
 *
 *  ----------           ----------
 *  |        |    Next   |        |    Next
 *  |   TOP  | --------> |  ....  | --------> NULL
 *  |        |           |        |
 *  ----------           ----------
 *
 *  After #stack_push:
 *
 *  ----------           ----------           ----------
 *  |        |    Next   |        |    Next   |        |    Next
 *  | #value | --------> |   TOP  | --------> |  ....  | --------> NULL
 *  |        |           | (prev) |           |        |
 *  ----------           ----------           ----------
 */
// ****************************************************************************************
void stack_push(Stack *stack, void *value) {
    SingleNode *new_node = malloc(sizeof(SingleNode));
    new_node->content = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}


// ****************************************************************************************
// stack_pop
// ****************************************************************************************
/**
 *  Pop the top of the #stack
 * @param[in]    stack Stack to pop first value
 * @param[out]   none
 * @return       Pointer to #stack top value
 *
 * @details
 *
 * Stack initial state:
 *
 *  ----------           ----------           ----------
 *  |        |    Next   |        |    Next   |        |    Next
 *  |   TOP  | --------> |    X   | --------> |  ....  | --------> NULL
 *  |        |           |        |           |        |
 *  ----------           ----------           ----------
 *
 *  After #stack_pop:
 *
 *  ----------           ----------
 *  |        |    Next   |        |    Next
 *  |    X   | --------> |  ....  | --------> NULL
 *  |  (TOP) |           |        |
 *  ----------           ----------
 */
// ****************************************************************************************
void * stack_pop(Stack *stack) {
    SingleNode *top = stack->top;
    if (top){
        void *content_to_return = top->content;
        stack->top = top->next;
        free(top);
        stack->size--;
        return content_to_return;
    }
    return NULL;
}

// ****************************************************************************************
// stack_peek
// ****************************************************************************************
/**
 *  Get the top value of #stack without removing it
 * @param[in]    stack  Stack to get first value
 * @param[out]   none
 * @return       Pointer to data stored on the first position of #stack (NULL if stack is empty)
 */
// ****************************************************************************************
inline void * stack_peek(Stack *stack) { return stack->top->content; }


// ****************************************************************************************
// stack_get_size
// ****************************************************************************************
/**
 *  Get the #stack current size
 * @param[in]    stack  Stack to obtain current size
 * @param[out]   none
 * @return       Size of #stack
 */
// ****************************************************************************************
inline unsigned int stack_get_size(Stack *stack) { return stack->size; }


// ****************************************************************************************
// stack_is_empty
// ****************************************************************************************
/**
 *  Check if #stack is empty
 * @param[in]    stack  Stack to check if is empty
 * @param[out]   none
 * @return       Stack empty
 */
// ****************************************************************************************
inline bool stack_is_empty(Stack *stack) { return stack->size == 0; }


// ****************************************************************************************
// stack_print
// ****************************************************************************************
/**
 *  Print all #stack elements starting from the top given a print function
 * @param[in]    stack       Stack to be printed
 * @param[in]    print_func  Function pointer to print value
 * @param[out]   none
 * @return       none
 */
// ****************************************************************************************
void stack_print(Stack *stack, void (*print_func)(void *)) {
    SingleNode *node = stack->top;
    /*for (unsigned int i = 0; i < stack->size; ++i) {*/ // Equivalent solution
    while (node){
        print_func(node->content);
        node = node->next;
    }
}


// ****************************************************************************************
// stack_destroy
// ****************************************************************************************
/**
 *  Delete all #stack structure, freeing node to node, value to value given #free_func
 * @param[in]    stack       Stack to be printed
 * @param[in]    print_func  Function pointer to free value
 * @param[out]   none
 * @return       none
 */
// ****************************************************************************************
void stack_destroy(Stack *stack, void(*free_func)(void*)){
    SingleNode *current_top = stack->top;
    SingleNode *previous_top;
    /*for (unsigned int i = 0; i < stack->size; i++) {*/
    while (current_top){
        previous_top = current_top;
        current_top = current_top->next;
        free_func(previous_top->content);
        free(previous_top);
    }

    free(stack);
}
