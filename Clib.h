/**
 * Copyright (C) 2019
 * Perseo Gutierrez Izquierdo <perseo.gi98@gmail.com>
 * 
 * @file Clib.h Function headers and type definitions for Clib.c
 *  
 */



#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CLIB_ERROR   (-1)
#define CLIB_OK      (0)
#define ELEMENT_ALREADY_EXIST (1)



/* Linked list headers */

struct node_l{
        void* content;
        struct node_l* prev;
        struct node_l* next;
};
typedef struct node_l node_l_t;

typedef struct{
        node_l_t* head;
        node_l_t* tail;
        int size;
} linked_list_t;



linked_list_t* create_linked_list();

void push_back(linked_list_t* l, void* value);

void* pop_front(linked_list_t* list);

void print_msg_list(linked_list_t* list);

/* HasMap headers */

struct node{
        char* key;
        void* content; // TODO : cambiar nombre por value
        struct node* next;
};

typedef struct node node_t;

typedef struct{
        int size;
        struct node **list;
} hash_map_t;


hash_map_t* create_hash_map(int size);

int insert_elem(hash_map_t* t, char* key, void* value);

int remove_elem(hash_map_t* t, char* key, void(*free_value)(void*));

void* lookup(hash_map_t* t, char* key);

void print_map(hash_map_t* t , void (*print)(void*));


/* LIBPULl headers */

typedef struct{
        int usr_size;
        int queue_size;
        int msg_size;
        char type;
}packet_head_t;

typedef struct{
        time_t timestamp;
        char* user;
        char* data;
}message_t;

typedef struct{
        char* queue_name;
        char* creator;
        time_t time_creation;
        int n_messages;
        linked_list_t* msg_list;
		linked_list_t* blocked_readers;
}group_t;

group_t* create_group(char* queue_name, char* creator);
void print_group(void* group);
void free_group(void* group);

// Defines
#define RECEIVE_ERROR			1

#define QUEUE_CREATED 			10
#define	QUEUE_ALREADY_EXIST		11
#define QUEUE_DELETED			12
#define QUEUE_DONT_EXIST		13
#define MESSAGE_SENT			14	
#define BLOCKED					15
