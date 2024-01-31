#include "list.h"
#include <stdlib.h>
#include <stdio.h>

// Gobal varialbes
//static List list;
List lists[LIST_MAX_NUM_HEADS]; // list of heads 
static int listCount = 0;
static Node nodeArr[LIST_MAX_NUM_NODES];
static int nodeCount;

static Stack stack;
static bool isStackInitialized = false; // should be done at first
static int stackTop = -1;
//static int stack_count = 0;

List* List_create(){
    if(!isStackInitialized){
        stackInit();
        isStackInitialized = true; 
    }
    
    int index = stackPop(); // index of heads-array
    printf("\n## %d ##\n", index);
    if(index == -1){
        return NULL; // not available any more
    }
    lists[index].head = NULL;
    lists[index].tail = NULL;
    lists[index].curr = NULL;
    lists[index].listsIndex = index;
    lists[index].count = 0;
    
    return &lists[index];
}

int List_count(List* pList){
    return pList->count;
}

void* List_first(List* pList){
    if(isEmpty(pList)){
        //pList->curr->item = NULL;
        return NULL;
    }
    void* tmp = pList->head->item;
    pList->head->item = pList->curr->item;
    return tmp;
}

void* List_last(List* pList){
    if(isEmpty(pList)){
        //pList->curr->item = NULL;
        return NULL;
    }
    pList->tail->item = pList->curr->item;
    return pList->tail;
}

void* List_next(List* pList){
    if(isEmpty(pList)) // zero node
        return NULL;
    pList->curr = pList->curr->next; 
    return pList->curr;
}

void* List_prev(List* pList){
    if(isEmpty(pList)) // zero node
        return NULL;
    pList->curr = pList->curr->prev; 
    return pList->curr;
}

void* List_curr(List* pList){
    return pList->curr;
}

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

int List_insert_after(List* pList, void* pItem){
    Node* added = createNode(pItem, pList);
    if(added == NULL){
        return LIST_FAIL; // failure
    }
    // success
    // case 0: Is 1st item
    if(pList->head == NULL){
        printf("(case 0)");
        pList->head = pList->tail = pList->curr = added;
        return LIST_SUCCESS;
    }
    // case 1: curr befor head
    if(pList->curr == NULL && (pList->curr->beforeHead) && !(pList->curr->beyondTail)){
        printf("(case 1)");
        return List_prepend(pList, pItem);
    }
    // case 2: curr beyond the end
    if(pList->curr == NULL && !(pList->curr->beforeHead) && (pList->curr->beyondTail)){
        printf("(case 2)");
        return List_append(pList, pItem);
    }
    // case 3: curr @inside of pList
    printf("(case 3)");
    Node* tmp = pList->curr->next;
    pList->curr->next = added;
    added->prev = pList->curr;
    added->next = tmp;
    if(tmp != NULL)
        tmp->prev = added;
    if(pList->curr == pList->tail)
        pList->tail = added;
    pList->curr = added; // curr is new node 
    return LIST_SUCCESS;
}

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
    // case 1: curr before the head
    if(pList->curr == NULL && (pList->curr->beforeHead) && !(pList->curr->beyondTail)){
        return List_prepend(pList, pItem);
    }
    // case 2: curr beyond the end
    if(pList->curr == NULL && !(pList->curr->beforeHead) && (pList->curr->beyondTail)){
        return List_append(pList, pItem);
    }
    // case 3: curr @inside of pList
    Node* tmp = pList->curr->prev;
    pList->curr->prev = added;
    added->prev = tmp;
    if(tmp != NULL) 
        tmp->next = added;
    added->next = pList->curr;
    if(pList->curr == pList->head)
        pList->head = added;
    pList->curr = added;
    return 0;
}

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

void* List_trim(List* pList){
    if(isEmpty(pList)){
        return NULL;
    }
    void* r = pList->tail->item;
    pList->tail->item = pList->curr->item;
    return r;
}

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
    return (pList->head == NULL);
}

Node* createNode(void* i, List* pList){
    if(nodeCount > LIST_MAX_NUM_NODES){
        return NULL;
    }
    Node* node = &nodeArr[nodeCount++];
    node->item = i;
    node->next = NULL;
    node->prev = NULL;

    node->beforeHead = false;
    node->beyondTail = false;  // initial state
    
    pList->count++;
    return node;
}

void ListStatus(List* pList){
    printf("\n=================\n");
    if (pList->head) {
        printf("head: %d\n", *(int*)(pList->head->item)); // Dereferencing the pointer
    } else {
        printf("head: NULL\n");
    }
    if (pList->curr) {
        printf("curr: %d\n", *(int*)(pList->curr->item));
    } else {
        printf("curr: NULL\n");
    }
    if (pList->tail) {
        printf("tail: %d\n", *(int*)(pList->tail->item));
    } else {
        printf("tail: NULL\n");
    }
    printf("count: %d\n", List_count(pList));
    printf("list-index: %d\n", pList->listsIndex);
    printf("=================\n");
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
    //stack_count = 0;
    stackTop = -1;
    for(int i = 0; i < LIST_MAX_NUM_HEADS; i++){
        stackPush(i);
        //stack_count++;
    }

    //------------------------
    printf("\n {");
    for(int i = 0; i < LIST_MAX_NUM_HEADS; i++){
        printf("%d, ", stack.indices[i]);
    }
    printf("}\n");
    //------------------------
}

int stackEmpty(){
    return stackTop == -1;
}

int stackFull(){
    return stackTop == LIST_MAX_NUM_HEADS-1;
}

void stackPush(int index){
     //printf("%d",index);
    if(!stackFull()){
        stack.indices[++stackTop] = index;
        //stackTop++;
    }
}

// returns free index of heads-array
int stackPop(){
    if(!stackEmpty()){
        int index = stack.indices[stackTop--];
        //stack_count--;
        return index;
    }
    return -1;
}