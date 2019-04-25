/*
 */
#include "Clib.h"


linked_list_t* create_linked_list(){

        linked_list_t* l = malloc(sizeof(linked_list_t));
        l->size = 0;
        l->head = malloc(sizeof(node_l_t));
        l->tail = malloc(sizeof(node_l_t));
        l->head->next = NULL;
        l->head->prev = l->tail;
        l->tail->next = l->head;
        l->tail->prev = NULL;

        return l;
}

void push_back(linked_list_t* l, void* value) {
        node_l_t* add = malloc(sizeof(node_l_t));
        add->content = value;

        l->tail->next->prev = add;      // Last element in queue set prev to new element
        add->next = l->tail->next;      // New element next set to last element in queue        
        add->prev = l->tail;   			// Set prev add element to queue tail 
		l->tail->next = add;            // Set tail element to new element
        l->size++;
}

void* pop_front(linked_list_t* list){
		if(list->size){
                node_l_t* head = list->head->prev;      // Get returning node

                list->head->prev = head->prev;  // Set new head to previous element of the beginning
				head->prev->next = list->head;  // Set new head element next to head node
                void* content = head->content;
                free(head);
				list->size--;
				return content;         // Remember to free content after use!!!
        }
        return NULL;
}

void print_msg_list(linked_list_t* list){

//    	printf("\nPRINT MSG LIST     !!!!!!!!!!! \n");
        node_l_t* node = list->head->prev;
        message_t* m;
		struct tm tm;
		for( int i = 0; i < list->size; i++){
//		while(node->content != NULL){
				m = (message_t*) node->content;
                tm = *localtime(&m->timestamp);
				printf("\tTimestamp: %d-%d-%d %d:%d:%d\n\tUser: %s\n\tData: %s\n", 
					tm.tm_year + 1900, 
					tm.tm_mon + 1, 
					tm.tm_mday, 
					tm.tm_hour, 
					tm.tm_min, 
					tm.tm_sec, 
					m->user,
					m->data);
                
				node = node->prev;
        }
}


// HASH MAP

hash_map_t* create_hash_map(int size){
        hash_map_t* table = malloc (sizeof(hash_map_t));
        table->size = size;
        table->list = (node_t**) malloc(sizeof(node_t*) * size);
        
        for(int i = 0; i < size; i++)
                table->list[i] = NULL;
        return table;
}


int hash_code(hash_map_t* t, char* key){
    int pos;
    for(int i = 0; i < strlen(key); i++)
        pos += key[i];
    return pos % t->size;
}


// TODO, pass a function to make the proper mallocs
int insert_elem(hash_map_t* t, char* key, void* value){
        int pos = hash_code(t, key);
        node_t* tmp = t->list[pos];
        while(tmp){ 
                if(strcmp(tmp->key,key) == 0){
                   // tmp->content = value;		// This impl doesnt allow value to be changed
                    return ELEMENT_ALREADY_EXIST;
                }
                tmp = tmp->next;
        }
		// If key does not exist, create a node
        node_t* new_elem = malloc(sizeof(node_t));
        new_elem->key = malloc(strlen(key));
		strcpy(new_elem->key,key);
        new_elem->content = value;
        new_elem->next = t->list[pos];
		t->list[pos] = new_elem;
		
	return CLIB_OK;
}

void* lookup(hash_map_t* t, char* key){
    int pos = hash_code(t,key);
	node_t* tmp = t->list[pos];
	while(tmp){
		if(strcmp(tmp->key, key) == 0){
			return tmp->content;
		}
		tmp = tmp->next;
	}
	return NULL;
}



int remove_elem(hash_map_t* t, char* key, void(*free_value)(void*)){
	   	
   //	printf("REMOVING !!");
	int pos = hash_code(t, key);
    node_t* tmp = t->list[pos];
	node_t* prev = NULL;

    while(tmp){
    	if(strcmp(tmp->key,key) == 0){
	    	if(prev != NULL){
				prev->next = tmp->next;
			}
			else{
				t->list[pos] = tmp->next;
			}	
			//(*free)(tmp->content);	// Call proper free function for our value structure
			free_group(tmp->content);
			free(tmp->content);
    		free(tmp);
			return CLIB_OK;
		}
		prev = tmp;
        tmp = tmp->next;
  	}
	 return CLIB_ERROR;
}


// Proper print function has to be created in order to print content fields of each value
void print_map(hash_map_t* t, void(*print)(void*)){
        node_t* tmp;
		int cont = 0;
		printf("\nHASH MAP\n");
        for(int i = 0; i < t->size; i++){
                tmp = t->list[i];
				
                while(tmp){
					printf("Elem: %d\n---------------------------\n",cont); 
                    (*print)(tmp->content);
					tmp = tmp->next;
					cont++;
                }
        }
}

// TODO: move to broker.c
// Free function for group_t 
void free_group(void* group) {
	group_t* g = (group_t*) group;
	free(g->queue_name);
	free(g->creator);
	printf("\n\nFreed group!\n\n\n");
}

// Print function for groups TODO: move to broker.c
void print_group(void* group){
		group_t* g = (group_t*) group;
        printf("\tCola: %s\n\tCreador: %s\n\tHora creacion: %ld\n\tnº mensages: %d\n",
                g->queue_name,
                g->creator,
                g->time_creation,
                g->n_messages);
       //  print_msg_list(g->msg_list);
}

group_t* create_group(char* queue_name, char* creator){
	group_t* new_group = malloc(sizeof(group_t));
	new_group->queue_name = malloc(strlen(queue_name));
    strcpy(new_group->queue_name, queue_name);

    new_group->creator = malloc(strlen(creator));
    strcpy(new_group->creator, creator);
    new_group->time_creation = time(NULL);
    new_group->n_messages = 0;	
		
	new_group->msg_list = (linked_list_t* ) create_linked_list();
	new_group->blocked_readers = (linked_list_t* ) create_linked_list();

	return new_group;
}
