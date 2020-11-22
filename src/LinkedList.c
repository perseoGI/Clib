// ****************************************************************************************
/**
 * @file   LinkedList.c
 * @brief  Custom implementation of Linked List on C
 *
 * @details This source file includes a Linked List implementation.
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
//                               Linked List API                                         //
//                                                                                       //
//=======================================================================================//

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/

bool compareInts(void *pattern, void *current){
    return *(int*)pattern == *(int*)current;
}

bool compareFloats(void *pattern, void *current){
    return *(float*)pattern == *(float*)current;
}

bool compareDoubles(void *pattern, void *current){
    return *(double*)pattern == *(double*)current;
}

bool compareStrings(void *pattern, void *current){
    return !strcmp((char*)pattern, (char*)current);
}

ContentComparator COMPARE_INT = compareInts;
ContentComparator COMPARE_FLOAT = compareFloats;
ContentComparator COMPARE_DOUBLE = compareDoubles;
ContentComparator COMPARE_STRING = compareStrings;

/******************************************************************************/
/*********************** Public Functions Implementations *********************/
/******************************************************************************/

// ****************************************************************************************
// create_linked_list
// ****************************************************************************************
/**
 *  Initialice linked list
 * @param[in]    none
 * @param[out]   none
 * @return       valid pointer to linked list structure
 *
 * @details
 *
 * Linked List initial state:
 *
 *
 *          Next   ----------    Next   ----------
 *  NULL <-------- |        | <-------- |        |
 *                 |  HEAD  |    Prev   |  TAIL  |     Prev
 *                 |        | --------> |        |  --------> NULL
 *                 ----------           ----------
 */
// ****************************************************************************************
LinkedList *create_linked_list(void) {

    LinkedList *l = malloc(sizeof(LinkedList));
    l->size = 0;
    l->head = malloc(sizeof(ListNode));
    l->tail = malloc(sizeof(ListNode));
    l->head->next = NULL;
    l->head->prev = l->tail;
    l->tail->next = l->head;
    l->tail->prev = NULL;
    // Needed to return NULL when list is empty
    l->head->content = NULL;
    l->tail->content = NULL;

    return l;
}


// ****************************************************************************************
// list_push_front
// ****************************************************************************************
/**
 *  Insert #value on the first position of #list
 * @param[in]    list  Linked list to insert #value
 * @param[in]    value Pointer to data to be stored on the first position of list
 * @param[out]   none
 * @return       none
 *
 * @details
 *
 * Linked List initial state:
 *
 *
 *          Next   ----------    Next   ----------     Next   ----------
 *  NULL <-------- |        | <-------- |        |  <-------- |        |
 *                 |  HEAD  |    Prev   |  ....  |     Prev   |  TAIL  |     Prev
 *                 |        | --------> |        |  --------> |        |  --------> NULL
 *                 ----------           ----------            ----------
 *
 *  After #list_push_front:
 *
 *          mext   ----------    next   ----------     next   ----------     next   ----------
 *  null <-------- |        | <-------- |        |  <-------- |        |  <-------- |        |
 *                 |  head  |    prev   | #value |     prev   |  ....  |     prev   |  tail  |     prev
 *                 |        | --------> |        |  --------> |        |  --------> |        |  --------> null
 *                 ----------           ----------            ----------            ----------
 */
// ****************************************************************************************
void list_push_front(LinkedList *list, void *value) {
    ListNode *add = malloc(sizeof(ListNode));
    add->content = value;

    list->head->prev->next = add;
    add->prev = list->head->prev;
    add->next = list->head;
    list->head->prev = add;
    list->size++;
}

// ****************************************************************************************
// list_push_back
// ****************************************************************************************
/**
 *  Insert #value on the last position of #list
 * @param[in]    list  Linked list to insert #value
 * @param[in]    value Pointer to data to be stored on the last position of list
 * @param[out]   none
 * @return       none
 *
 * @details
 *
 * Linked List initial state:
 *
 *
 *          Next   ----------    Next   ----------     Next   ----------
 *  NULL <-------- |        | <-------- |        |  <-------- |        |
 *                 |  HEAD  |    Prev   |  ....  |     Prev   |  TAIL  |     Prev
 *                 |        | --------> |        |  --------> |        |  --------> NULL
 *                 ----------           ----------            ----------
 *
 *  After #list_push_back:
 *
 *          mext   ----------    Next   ----------     Next   ----------     Next   ----------
 *  NULL <-------- |        | <-------- |        |  <-------- |        |  <-------- |        |
 *                 |  HEAD  |    Prev   |  ....  |     Prev   | #value |     Prev   |  TAIL  |     Prev
 *                 |        | --------> |        |  --------> |        |  --------> |        |  --------> NULL
 *                 ----------           ----------            ----------            ----------
 */
// ****************************************************************************************
void list_push_back(LinkedList *l, void *value) {
    ListNode *add = malloc(sizeof(ListNode));
    add->content = value;

    l->tail->next->prev = add; // Last element in queue set prev to new element
    add->next = l->tail->next; // New element next set to last element in queue
    add->prev = l->tail;       // Set prev add element to queue tail
    l->tail->next = add;       // Set tail element to new element
    l->size++;
}


// ****************************************************************************************
// list_pop_front
// ****************************************************************************************
/**
 *  Extract first value of #list, returning it
 * @param[in]    list  Linked list to pop first value
 * @param[out]   none
 * @return       Pointer to data stored on the first position of #list
 *
 * @details
 *
 * Linked List initial state:
 *
 *          mext   ----------    next   ----------     next   ----------     next   ----------
 *  null <-------- |        | <-------- |        |  <-------- |        |  <-------- |        |
 *                 |  head  |    prev   |  First |     prev   |  ....  |     prev   |  tail  |     prev
 *                 |        | --------> |        |  --------> |        |  --------> |        |  --------> null
 *                 ----------           ----------            ----------            ----------
 *
 *  After #list_pop_front:
 *
 *          mext   ----------    Next   ----------    Next   ----------
 *  NULL <-------- |        | <-------- |        | <-------- |        |
 *                 |  HEAD  |    Prev   |  ....  |    Prev   |  TAIL  |     Prev
 *                 |        | --------> |        | --------> |        |  --------> NULL
 *                 ----------           ----------           ----------
 */
// ****************************************************************************************
void * list_pop_front(LinkedList *list) {
    if (list->size) {
        ListNode *head = list->head->prev; // Get returning node

        list->head->prev =
            head->prev; // Set new head to previous element of the beginning
        head->prev->next = list->head; // Set new head element next to head node
        void *content = head->content;
        free(head);
        list->size--;
        return content; // Remember to free content after use!!!
    }
    return NULL;
}

// ****************************************************************************************
// list_pop_back
// ****************************************************************************************
/**
 *  Extract last value of #list, returning it
 * @param[in]    list  Linked list to pop last value
 * @param[out]   none
 * @return       Pointer to data stored on the last position of #list
 *
 * @details
 *
 * Linked List initial state:
 *
 *          mext   ----------    next   ----------     next   ----------     next   ----------
 *  null <-------- |        | <-------- |        |  <-------- |        |  <-------- |        |
 *                 |  head  |    prev   |  First |     prev   |  ....  |     prev   |  tail  |     prev
 *                 |        | --------> |        |  --------> |        |  --------> |        |  --------> null
 *                 ----------           ----------            ----------            ----------
 *
 *  After #list_pop_back:
 *
 *          mext   ----------    Next   ----------    Next   ----------
 *  NULL <-------- |        | <-------- |        | <-------- |        |
 *                 |  HEAD  |    Prev   |  ....  |    Prev   |  TAIL  |     Prev
 *                 |        | --------> |        | --------> |        |  --------> NULL
 *                 ----------           ----------           ----------
 */
// ****************************************************************************************
void * list_pop_back(LinkedList *list) {
    if (list->size) {
        ListNode *lastNode = list->tail->next; // Get returning node

        list->tail->next = lastNode->next; // Set new tail to next element of the last node
        lastNode->next->prev = list->tail;
        void *content = lastNode->content;
        free(lastNode);
        list->size--;
        return content; // Remember to free content after use!!!
    }
    return NULL;
}

// ****************************************************************************************
// list_get_first
// ****************************************************************************************
/**
 *  Get the first value of #list without extracting the node
 * @param[in]    list  Linked list to get first value
 * @param[out]   none
 * @return       Pointer to data stored on the first position of #list (NULL if list is empty)
 */
// ****************************************************************************************
void * list_get_first(LinkedList *list) { return list->head->prev->content; }

// ****************************************************************************************
// list_get_last
// ****************************************************************************************
/**
 *  Get the last value of #list without extracting the node
 * @param[in]    list  Linked list to get last value
 * @param[out]   none
 * @return       Pointer to data stored on the last position of #list (NULL if list is empty)
 */
// ****************************************************************************************
void * list_get_last(LinkedList *list) { return list->tail->next->content; }

// ****************************************************************************************
// list_get_size
// ****************************************************************************************
/**
 *  Get the list current size
 * @param[in]    list  Linked list to obtain current size
 * @param[out]   none
 * @return       Size of list
 */
// ****************************************************************************************
inline unsigned int list_get_size(LinkedList *list) { return list->size; }


// ****************************************************************************************
// list_get_element
// ****************************************************************************************
/**
 *  Get element of list given a #postion
 * @param[in]    list      Linked list to get element
 * @param[in]    position  Position inside list
 * @param[out]   none
 * @return       Element on given position
 */
// ****************************************************************************************
void * list_get_element(LinkedList *list, unsigned int position) {
    unsigned int size = list->size;
    ListNode *node;

    if (position >= size)
        return NULL;    // Maybe return error

    if (position < size / 2){
        node = list->head->prev;
        while (position--)
        /*for (int i = 0; i <= position; ++i)*/
            node = node->prev;
    } else {
        node = list->tail->next;
        for (unsigned int i = size - 1; i > position; --i)
            node = node->next;
    }

    return node->content;
}


// ****************************************************************************************
// list_find_node
// ****************************************************************************************
/**
 *  Find and return first #list node which match pattern
 * @param[in]    list       Linked list to find node
 * @param[in]    pattern    Content node to find
 * @param[in]    comparator    Function which compares node contents
 * @param[out]   none
 * @return       Node with content matching given #pattern
 */
// ****************************************************************************************
ListNode * list_find_node(LinkedList *list, void * pattern, ContentComparator comparator) {
    ListNode *node = list->head->prev;
    for (unsigned int i = 0; i < list->size; ++i){
        if (comparator(pattern, node->content)){
            return node;
        }
        node = node->prev;
    }

    return NULL;
}


// ****************************************************************************************
// list_print
// ****************************************************************************************
/**
 *  Print all list elements starting from the first element given a print function
 * @param[in]    list  Linked list to be printed
 * @param[in]    print_func  Function pointer to print value
 * @param[out]   none
 * @return       none
 */
// ****************************************************************************************
void list_print(LinkedList *list, void (*print_func)(void *)) {
    ListNode *node = list->head->prev;
    for (unsigned int i = 0; i < list->size; i++) {
        print_func(node->content);
        node = node->prev;
    }
}


// TODO comment out FREE_TO_NULL not working
void list_destroy(LinkedList *list){
    ListNode *current = list->head->prev;
    ListNode *previous;
    for (unsigned int i = 0; i < list->size; i++) {
        previous = current;
        current = current->prev;
        /*free(previous->content);*/
        free(previous);
    }

    free(list->head);
    free(list->tail);
    free(list);
}

