#include "list.h"
#include <stdlib.h>

// Gobal varialbes
static List list;

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create(){
    list.head = NULL;
    list.tail = NULL;
    list.curr = NULL;
    return &list;
}

// Returns the number of items in pList.
int List_count(List* pList){
    int count = 0;
    Node* curr = pList->head;
    while(curr != pList->tail){
        curr = curr->next;
        count++;
    }
    return count+1; // add last node
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
void* List_next(List* pList);


//-----------------------------------------
// private function
//-----------------------------------------
bool isEmpty(List* pList){
    return (pList->head == NULL) && (pList->tail == NULL);
}