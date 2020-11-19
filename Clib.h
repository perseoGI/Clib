// ****************************************************************************************
/**
 * @file   Clib.h
 * @brief  Custom implementation of useful data structures on C
 *
 * @details This source file includes a Linked List implementation and a Hash Map implementation.
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

#ifndef CLIB_H
#define CLIB_H

// ****************************************************************************************
// ********************************** Include Files ***************************************
// ****************************************************************************************

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// ****************************************************************************************
// ****************************** Definitions & Constants *********************************
// ****************************************************************************************

#define CLIB_OK                         (0)
#define CLIB_ERROR                      (1)
#define E_ELEMENT_ALREADY_EXIST         (2)




//=======================================================================================//
//                                                                                       //
//                               Linked List API                                         //
//                                                                                       //
//=======================================================================================//


/********************************** STRUCTURES **************************************/

/// Internal Linked List node
struct list_node{
    void* content;              //< Pointer to storing node data
    struct list_node* prev;        //< Pointer to previous node
    struct list_node* next;        //< Pointer to next node
};

/// External Linked List node definition
typedef struct list_node ListNode;

/// Linked List structure
typedef struct{
    ListNode* head;             //< Pointer to list head (this will not point to any content)
    ListNode* tail;             //< Pointer to list tail (this will not point to any content)
    int size;                   //< Current Linked List size (could be calculated but this increase performance)
} LinkedList;


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
LinkedList *create_linked_list(void);


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
void list_push_front(LinkedList *list, void *value);


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
void list_push_back(LinkedList *l, void *value);


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
void * list_pop_front(LinkedList *list);


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
void * list_pop_back(LinkedList *list);


// ****************************************************************************************
// list_get_first
// ****************************************************************************************
/**
 *  Get the first value of #list without extracting the node
 * @param[in]    list  Linked list to get first value
 * @param[out]   none
 * @return       Pointer to data stored on the first position of #list
 */
// ****************************************************************************************
void * list_get_first(LinkedList *list);


// ****************************************************************************************
// list_get_last
// ****************************************************************************************
/**
 *  Get the last value of #list without extracting the node
 * @param[in]    list  Linked list to get last value
 * @param[out]   none
 * @return       Pointer to data stored on the last position of #list
 */
// ****************************************************************************************
void * list_get_last(LinkedList *list);


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
int list_get_size(LinkedList *list);


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
void list_print(LinkedList *list, void (*print_func)(void *));



//=======================================================================================//
//                                                                                       //
//                                  Hash Map API                                         //
//                                                                                       //
//=======================================================================================//

/// Private Hash Map node
struct hashmap_node{
    char* key;                  //< Key of key-value pair
    void* value;                //< Value of key-value pair
    struct hashmap_node* next;  //< Next Node on the single linked list chain
};

/// Public definition of Hash Map Node
typedef struct hashmap_node MapNode;

/// Hash Map structure
typedef struct{
    int size;                   //< Fixed size of hash map (number of table entries)
    MapNode **list;             //< Table of list nodes
} HashMap;


// ****************************************************************************************
// create_hash_map
// ****************************************************************************************
/**
 *  Initialice a Hash Map with a fixed #size
 * @param[in]    size  Size for the Hash Map
 * @param[out]   none
 * @return       Pointer to a valid Hash Map structure
 *
 * @details
 *
 * Hash Map initial state:
 *
 *  |---------|
 *  |         |
 *  |    x----+-----> NULL
 *  |         |
 *  |---------|
 *  |---------|
 *  |         |
 *  |    x----+-----> NULL
 *  |         |
 *  |---------|
 *  |---------|
 *  |         |
 *  |    x----+-----> NULL
 *  |         |
 *  |---------|
 *
 */
// ****************************************************************************************
HashMap * create_hash_map(int size);


// ****************************************************************************************
// hash_map_set
// ****************************************************************************************
/**
 *  Set a key-value pair on #map. If key already exist, update its value
 * @param[in]    map        Hash Map to be set
 * @param[in]    key        Key of pair key-value
 * @param[in]    value      Value of pair key-value
 * @return       Pointer to previous value if #key already exists, or NULL in other case
 *
 * @details
 *
 * Hash Map initial state:                          Hash Map after #hash_map_set:
 *
 *  |---------|                                    |---------|
 *  |         |                                    |         |
 *  |    x----+-----> NULL                         |    x----+-----> NULL
 *  |         |                                    |         |
 *  |---------|                                    |---------|
 *  |---------|                                    |---------|       -----------------
 *  |         |                                    |         |       | #Key | #Value |
 *  |    x----+-----> NULL                         |    x----+-----> -----------------
 *  |         |                                    |         |       |   Next  x-----+---> NULL
 *  |---------|                                    |---------|       -----------------
 *  |---------|                                    |---------|
 *  |         |                                    |         |
 *  |    x----+-----> NULL                         |    x----+-----> NULL
 *  |         |                                    |         |
 *  |---------|                                    |---------|
 *
 * Collision case: if a collision happens, new node is inserted in the BEGINING of the list given current position
 *
 * Hash Map initial state:                          Hash Map after #hash_map_set (collision case):
 *
 *  |---------|       ---------------              |---------|       -----------------      ---------------
 *  |         |       | Key | Value |              |         |       | #Key | #Value |      | Key | Value |
 *  |    x----+-----> ---------------              |    x----+-----> -----------------   -->---------------
 *  |         |       |   Next  x---+----> NULL    |         |       |   Next  x-----+---|  |   Next  x---+---> NULL
 *  |---------|       ---------------              |---------|       -----------------      ---------------
 *  |---------|       ---------------              |---------|       ---------------
 *  |         |       | Key | Value |              |         |       | Key | Value |
 *  |    x----+-----> ---------------              |    x----+-----> ---------------
 *  |         |       |   Next  x---+----> NULL    |         |       |   Next  x---+-----> NULL
 *  |---------|       ---------------              |---------|       ---------------
 *  |---------|                                    |---------|
 *  |         |                                    |         |
 *  |    x----+-----> NULL                         |    x----+-----> NULL
 *  |         |                                    |         |
 *  |---------|                                    |---------|
 */
// ****************************************************************************************
void * hash_map_set(HashMap *map, char *key, void *value);


// ****************************************************************************************
// hash_map_remove
// ****************************************************************************************
/**
 *  Remove a key-value pair on #map given a #key
 * @param[in]    map        Hash Map to remove pair
 * @param[in]    key        Key of pair key-value to be removed
 * @param[in]    free_value Function to free value
 * @return       CLIB_OK    if key exist \n
 *               CLIB_ERROR if key does not exist
 *
 * @notes        If value to be removed is needed, use #hash_map_pop insetead
 * @details
 *
 * Hash Map initial state:                          Hash Map after #hash_map_remove:
 *
 *  |---------|                                   |---------|
 *  |         |                                   |         |
 *  |    x----+-----> NULL                        |    x----+-----> NULL
 *  |         |                                   |         |
 *  |---------|                                   |---------|
 *  |---------|       ----------------            |---------|
 *  |         |       | #Key | Value |            |         |
 *  |    x----+-----> ----------------            |    x----+-----> NULL
 *  |         |       |   Next  x----+---> NULL   |         |
 *  |---------|       ----------------            |---------|
 *  |---------|                                   |---------|
 *  |         |                                   |         |
 *  |    x----+-----> NULL                        |    x----+-----> NULL
 *  |         |                                   |         |
 *  |---------|                                   |---------|
 *
 * Collision case: if a collision happens, new node is inserted in the BEGINING of the list given current position
 *
 * Hash Map initial state:                                              Hash Map after #hash_map_remove (collision case):
 *
 *  |---------|       ----------------      ---------------           |---------|       ---------------
 *  |         |       | #Key | Value |      | Key | Value |           |         |       | Key | Value |
 *  |    x----+-----> ----------------   -->---------------           |    x----+-----> ---------------
 *  |         |       |   Next  x----+---|  |   Next  x---+---> NULL  |         |       |   Next  x---+----> NULL
 *  |---------|       ----------------      ---------------           |---------|       ---------------
 *  |---------|       ---------------                                 |---------|       ---------------
 *  |         |       | Key | Value |                                 |         |       | Key | Value |
 *  |    x----+-----> ---------------                                 |    x----+-----> ---------------
 *  |         |       |   Next  x---+-----> NULL                      |         |       |   Next  x---+----> NULL
 *  |---------|       ---------------                                 |---------|       ---------------
 *  |---------|                                                       |---------|
 *  |         |                                                       |         |
 *  |    x----+-----> NULL                                            |    x----+-----> NULL
 *  |         |                                                       |         |
 *  |---------|                                                       |---------|
 */
// ****************************************************************************************
int hash_map_remove(HashMap *map, char *key, void (*free_value)(void *));


// ****************************************************************************************
// hash_map_pop
// ****************************************************************************************
/**
 *  Remove a key-value pair on #map given a #key and return value
 * @param[in]    map        Hash Map to remove pair
 * @param[in]    key        Key of pair key-value to be removed
 * @param[in]    free_value Function to free value
 * @return       CLIB_OK    if key exist \n
 *               CLIB_ERROR if key does not exist
 *
 * @details      Very similar to #hash_map_remove
 */
// ****************************************************************************************
void * hash_map_pop(HashMap *map, char *key);


// ****************************************************************************************
// hash_map_get
// ****************************************************************************************
/**
 *  Get a key-value pair on #map given a #key
 * @param[in]    map        Hash Map to obtain value
 * @param[in]    key        Key of pair key-value to obtain
 * @return       Pointer value if #key exists, or NULL if it does not exist
 */
// ****************************************************************************************
void * hash_map_get(HashMap *map, char *key);


// ****************************************************************************************
// hash_map_print
// ****************************************************************************************
/**
 *  Print all elements on #map starting from the first position of the map,
 * iterating over every list node on position given a print function
 * @param[in]    map         Hash Map to be printed
 * @param[in]    print_func  Function pointer to print value
 * @param[out]   none
 * @return       none
 */
// ****************************************************************************************
void hash_map_print(HashMap* t , void (*print)(void*));

#endif // CLIB_H
