#include "list.h"
#include <stdlib.h>
#include <stdio.h>

// Gobal varialbes
//static List list;
List lists[LIST_MAX_NUM_HEADS]; // list of heads 
static int listCount = 0;
static nodeArr[LIST_MAX_NUM_NODES];
static int nodeCount;

static Stack stack;
static bool isStackInitialized = false; // should be done at first
static int stackTop = -1;

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create(){
    if(!isStackInitialized){
        stackInit();
        isStackInitialized = true; 
    }
    
    int index = stackPop(); // index of heads-array
    if(index == -1){
        return NULL; // not available any more
    }
    lists[index].head = NULL;
    lists[index].tail = NULL;
    lists[index].curr = NULL;
    lists[index].listsIndex = index;
    
    return &lists[index];
}

// Returns the number of items in pList.
int List_count(List* pList){
    return pList->count;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    if(isEmpty(pList)){
        pList->curr->item = NULL;
        return NULL;
    }
    pList->head->item = pList->curr->item;
    return (pList->head->item);
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
    if(isEmpty(pList)) // zero node
        return NULL;
    pList->curr = pList->curr->next; 
    return pList->curr;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
    if(isEmpty(pList)) // zero node
        return NULL;
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
    Node* added = createNode(pItem, pList);
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
    Node* added = createNode(pItem, pList);
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
    Node* added = createNode(pItem, pList);
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
    Node* added = createNode(pItem, pList);
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

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    if(pList->curr == NULL){
        return NULL;
    }
    // case 0: one node, curr is head
    pList->count--;
    void* r = pList->curr->item;
    if(pList->curr == pList->head){
        pList->head->item = NULL;
        pList->curr->item = NULL;
        return r;
    }
    // case 1: curr is tail
    if(pList->curr == pList->tail){
        pList->curr = pList->curr->next; // NULL
        pList->tail = pList->tail->prev;
        pList->tail->next = NULL;
        return r;
    }
    // case 2: inside
    Node* tmpNode = pList->curr->next;
    pList->curr->prev->next = pList->curr->next;
    pList->curr->next->prev = pList->curr->prev;
    tmpNode->item = r;
    return r;
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    if(isEmpty(pList)){
        return NULL;
    }
    void* r = pList->tail->item;
    pList->tail->item = pList->curr->item;
    return r;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    if(isEmpty(pList1) || isEmpty(pList2)) return;
    pList1->tail->next = pList2->head;
    pList2->head->prev = pList1->tail;
    pList1->tail = pList2->tail;

    pList1->count += pList2->count;
    
    pList2->head = NULL;
    pList2->curr = NULL;
    pList2->tail = NULL;
    stackPush(pList2->listsIndex);
}


void List_free(List* pList, FREE_FN pItemFreeFn){
    if(pList == NULL) return;
    Node* node = pList->head;
    while(node != NULL){
        if(pItemFreeFn != NULL && node->item != NULL){
            (*pItemFreeFn)(node->item);
        }
        node = node->next;
    }

    pList->head = NULL;
    pList->curr = NULL;
    pList->tail = NULL;
    pList->count = 0;
    stackPush(pList->listsIndex);
}

void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    Node* node = pList->curr;
    while(node != NULL){
        if(pComparator(node->item, pComparisonArg)){
            // match
            pList->curr = node;
            return node->item;
        }
        node = node->next;
    }
    // no match
    pList->curr = NULL;
    return NULL;
}


//-----------------------------------------
// private function
//-----------------------------------------
bool isEmpty(List* pList){
    return (pList->head == NULL) && (pList->tail == NULL);
}

Node* createNode(void* i, List* pList){
    if(nodeCount > LIST_MAX_NUM_NODES){
        return NULL;
    }
    Node* node = &nodeArr[nodeCount++];
    node->item = i;
    node->next = NULL;
    node->prev = NULL;
    //node->index = pList->count;
    pList->count++;
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

// void printArr(){
//     printf("\n{");
//     for(int i = 0; i < nodeCount; i++){
//         printf("%p ", nodeArr[i].item);
//     }
//     printf("}\n");
// }

//--------------------------------
//Stack functions 
//--------------------------------
void stackInit(){
    for(int i = 0; i < LIST_MAX_NUM_HEADS; i++){
        push(i);
    }
    // stackTop is now 9 (10th)
}

int stackEmpty(){
    return stackTop == -1;
}

int stackFull(){
    return stackTop = LIST_MAX_NUM_HEADS-1;
}

void stackPush(int index){
    if(!stackFull()){
        stack.indices[++stackTop] = index;
    }
}

// returns free index of heads-array
int stackPop(){
    if(!stackEmpty()){
        int index = stack.indices[stackTop--];
        return index;
    }
    return -1;
}