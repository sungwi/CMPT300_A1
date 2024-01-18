#include "list.h"
#include <stdlib.h>
#include <stdio.h>

// Gobal varialbes
static List list;
static Node nodeArr[LIST_MAX_NUM_NODES];
static int count = 0;

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create(){
    list.head = NULL;
    list.tail = NULL;
    list.curr = NULL;

    for(int i = 0; i < LIST_MAX_NUM_NODES; i++){
        nodeArr[i].item = NULL;
        nodeArr[i].next = NULL;
        nodeArr[i].prev = NULL;
    }

    return &list;
}

// Returns the number of items in pList.
int List_count(List* pList){
    // int count = 0;
    // Node* curr = pList->head;
    // while(curr != pList->tail){
    //     curr = curr->next;
    //     count++;
    // }
    // return count+1; // add last node
    return count;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    if(isEmpty(pList)){
        pList->curr->item = NULL;
        return NULL;
    }
    pList->head->item = pList->curr->item;
    return pList->head;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
    if(isEmpty(pList)){
        pList->curr->item = NULL;
        return NULL;
    }
    pList->tail->item = pList->curr->item;
    return pList->tail;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){
    pList->curr = pList->curr->next; 
    return pList->curr;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
    pList->curr = pList->curr->prev; 
    return pList->curr;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){
    return pList->curr;
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    Node* added = createNode(pItem);
    if(added == NULL){
        return -1; // failure
    }
    // success
    pList->tail->next = added;
    added->prev = pList->tail;
    pList->tail = added; // move tail
    pList->curr = added;
    return 0;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
    Node* added = createNode(pItem);
    if(added == NULL){
        return -1; // failure
    }
    // success
    added->next = pList->head;
    pList->head->prev = added;
    pList->head = added; // move head
    pList->curr = added;
    return 0;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem){
    Node* added = createNode(pItem);
    if(added == NULL){
        return -1; // failure
    }
    // success
    // case 0: Is 1st item
    if(pList->head == NULL){
        pList->head = pList->tail = pList->curr = added;
        return 0;
    }
    // case 1: curr @start
    if(pList->curr == pList->head){
        return List_append(pList, pItem);
    }
    // case 2: curr @beyond the end
    if(pList->curr == NULL){
        return List_prepend(pList, pItem);
    }
    // case 3: curr @inside of pList
    Node* tmp = pList->curr->next;
    pList->curr->next = added;
    added->prev = pList->curr;
    added->next = tmp;
    pList->curr = added;
    return 0;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem){
    Node* added = createNode(pItem);
    if(added == NULL){
        return -1; // failure
    }
    // success
    // case 0: Is 1st item
    if(pList->head == NULL){
        pList->head = pList->tail = pList->curr = added;
        return 0;
    }
    // case 1: curr @start
    if(pList->curr == pList->head){
        return List_append(pList, pItem);
    }
    // case 2: curr @beyond the end
    if(pList->curr == NULL){
        return List_prepend(pList, pItem);
    }
    // case 3: curr @inside of pList
    Node* tmp = pList->curr->prev;
    pList->curr->prev = added;
    added->prev = tmp;
    added->next = pList->curr;
    pList->curr = added;
    return 0;
}


//-----------------------------------------
// private function
//-----------------------------------------
bool isEmpty(List* pList){
    return (pList->head == NULL) && (pList->tail == NULL);
    // return (count == 0);
}

Node* createNode(void* i){
    if(count > LIST_MAX_NUM_NODES){
        return NULL;
    }
    Node* node = &nodeArr[count++];
    node->item = i;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void printList(List* pList){
    Node* n = pList->head;
    printf("\n[");
    while(n != NULL){
        int* intPtr = (int*)(n->item);
        printf("%d ", *intPtr);
        //printf("%p ", n->item);
        n = n->next;
    }
    printf("]\n");
}

void printArr(){
    printf("\n{");
    for(int i = 0; i < count; i++){
        printf("%p ", nodeArr[i].item);
    }
    printf("}\n");
}