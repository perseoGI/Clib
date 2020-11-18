// ****************************************************************************************
/**
 * @file   Clib.c
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

// ****************************************************************************************
// ********************************** Include Files ***************************************
// ****************************************************************************************
#include "Clib.h"

//=======================================================================================//
//                                                                                       //
//                               Linked List API                                         //
//                                                                                       //
//=======================================================================================//

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
    list->tail->next = add;
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
void *list_pop_front(LinkedList *list) {
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
void *list_pop_back(LinkedList *list) {
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
 * @return       Pointer to data stored on the first position of #list
 */
// ****************************************************************************************
void *list_get_first(LinkedList *list) { return list->head->prev->content; }

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
void *list_get_last(LinkedList *list) { return list->tail->next->content; }

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
inline int list_get_size(LinkedList *list) { return list->size; }

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
    for (int i = 0; i < list->size; i++) {
        print_func(node->content);
        node = node->prev;
    }
}


//=======================================================================================//
//                                                                                       //
//                                  Hash Map API                                         //
//                                                                                       //
//=======================================================================================//


/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/

// ****************************************************************************************
// hash_code
// ****************************************************************************************
/*  Private function to calculate postion in hash table given #key
 * @param[in]    map        Hash Map to obtain position
 * @param[in]    key        Key to obtain position
 *
 * @details      this is a very simple implementation of a hash
 *
 */
// ****************************************************************************************
int hash_code(HashMap *map, char *key) {
    int pos = 0;
    for (int i = 0; i < (int)strlen(key); ++i)
        pos += key[i];
    return pos % map->size;
}

/******************************************************************************/
/*********************** Public Functions Implementations *********************/
/******************************************************************************/


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
HashMap * create_hash_map(int size) {
    HashMap *table = malloc(sizeof(HashMap));
    table->size = size;
    table->list = (MapNode **)malloc(sizeof(MapNode *) * (unsigned long)size);

    for (int i = 0; i < size; i++)
        table->list[i] = NULL;
    return table;
}



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
void * hash_map_set(HashMap *map, char *key, void *value) {
    int pos = hash_code(map, key);
    MapNode *tmp = map->list[pos];
    while (tmp) {
        // If key already exist, update value
        if (strcmp(tmp->key, key) == 0){
            void *prev_value = tmp->value;
            tmp->value = value;
            return prev_value;
        }

        tmp = tmp->next;
    }

    // If key does not exist, create a node
    MapNode *new_elem = malloc(sizeof(MapNode));
    new_elem->key = malloc(strlen(key));
    strcpy(new_elem->key, key);
    new_elem->value = value;
    // Insert new node in the beginning of the list
    new_elem->next = map->list[pos];
    map->list[pos] = new_elem;

    return NULL;
}


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
void * hash_map_get(HashMap *map, char *key) {
    int pos = hash_code(map, key);
    MapNode *tmp = map->list[pos];
    while (tmp) {
        if (strcmp(tmp->key, key) == 0) {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}


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
int hash_map_remove(HashMap *map, char *key, void (*free_value)(void *)) {

    int pos = hash_code(map, key);
    MapNode *tmp = map->list[pos];
    MapNode *prev = NULL;

    while (tmp) {
        if (strcmp(tmp->key, key) == 0) {
            if (prev != NULL) {
                prev->next = tmp->next;
            } else {
                map->list[pos] = tmp->next;
            }
            (*free_value)(tmp->value); // TODO: review. Call proper free function
            // for our value structure
            free(tmp->value);
            free(tmp);
            return CLIB_OK;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return CLIB_ERROR;
}


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
void * hash_map_pop(HashMap *map, char *key) {

    int pos = hash_code(map, key);
    MapNode *tmp = map->list[pos];
    MapNode *prev = NULL;

    while (tmp) {
        if (strcmp(tmp->key, key) == 0) {
            if (prev != NULL) {
                prev->next = tmp->next;
            } else {
                map->list[pos] = tmp->next;
            }
            void *value = tmp->value;
            free(tmp);
            return value;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return NULL;
}


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
void print_map(HashMap *map, void (*print_func)(void *)) {
    MapNode *tmp;
    int map_position = 0;
    printf("\nHASH MAP\n");
    for (int i = 0; i < map->size; i++) {
        tmp = map->list[i];
        while (tmp) {
            printf("Elem: %d\n---------------------------\n", map_position);
            (*print_func)(tmp->value);
            tmp = tmp->next;
            map_position++;
        }
    }
}
