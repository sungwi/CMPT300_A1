/*
    Course: CMPT 300 - Assignment 1
    Name: Sungwi Kim
    Student Number: 301592065
*/


#include "list.h"

// Gobal varialbes
static List lists[LIST_MAX_NUM_HEADS]; // list of heads 

static Node nodeArr[LIST_MAX_NUM_NODES];
static int nodeCount;
static Stack nodeStack; // keep track of index in pool
static bool isNodeStackInitialized = false;

static Stack stack;
static bool isStackInitialized = false; // should be done at first


//-----------------------------------------
// private function
//-----------------------------------------
static int stackEmpty(Stack* stack){
    return stack->top == -1;
}

static int stackFull(Stack* stack){
    return stack->top == stack->capacity - 1;
}

static void stackPush(Stack* stack, int index){
     //printf("%d",index);
    if(!stackFull(stack)){
        stack->indices[++stack->top] = index;
        //stackTop++;
    }
}

// returns free index of heads-array
static int stackPop(Stack* stack){
    if(!stackEmpty(stack)){
        int index = stack->indices[(stack->top)--];
        //stack_count--;
        return index;
    }
    return -1;
}

static void stackInit(Stack* stack, int capacity){
    //stack_count = 0;
    //stackTop = -1;
    stack->capacity = capacity;
    stack->top = -1;
    for(int i = 0; i < stack->capacity; i++){ //10 or 100
        stackPush(stack, i);
    }

    //------------------------
    printf("\n {");
    for(int i = 0; i < stack->capacity; i++){
        printf("%d, ", stack->indices[i]);
    }
    printf("}\n");
    //------------------------
}

static bool isEmpty(List* pList){
    return (pList->head == NULL);
}

static Node* createNode(void* i, List* pList){
    if(nodeCount >= LIST_MAX_NUM_NODES){
        return NULL;
    }
    nodeCount++;
    int nodeIndex = stackPop(&nodeStack);
    Node* node = &nodeArr[nodeIndex];
    node->item = i;
    node->next = NULL;
    node->prev = NULL;
    node->poolIndex = nodeIndex;
    
    pList->count++;
    return node;
}



//-----------------------------------------
// public function
//-----------------------------------------
List* List_create(){
    if(!isStackInitialized){
        stackInit(&stack, LIST_MAX_NUM_HEADS);
        isStackInitialized = true; 
    }
    if(!isNodeStackInitialized){
        stackInit(&nodeStack, LIST_MAX_NUM_NODES);
        isNodeStackInitialized = true;
        for(int i = 0; i < LIST_MAX_NUM_NODES; i++){
            nodeArr[i].item = NULL;
            nodeArr[i].next = NULL;
            nodeArr[i].prev = NULL;
            nodeArr[i].poolIndex = -1;
        }
    }
    
    int index = stackPop(&stack); // index of heads-array
    //printf("\n## %d ##\n", index);
    if(index == -1){
        return NULL; // not available any more
    }
    lists[index].head = NULL;
    lists[index].tail = NULL;
    lists[index].curr = NULL;
    lists[index].listsIndex = index;
    lists[index].count = 0;
    //printf("END list create\n");
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
    void* tmp = pList->tail->item;
    pList->tail->item = pList->curr->item;
    return tmp;
}

void* List_next(List* pList){
    if(isEmpty(pList) || pList->curr == NULL) // zero node
        return NULL;
    pList->curr = pList->curr->next; 
    if(pList->curr == NULL){
        pList->state = LIST_OOB_END;
        return NULL;
    }
    return pList->curr->item;
}

void* List_prev(List* pList){
    if(isEmpty(pList) || pList->curr == NULL) // zero node
        return NULL;
    pList->curr = pList->curr->prev; 
    if(pList->curr == NULL){
        pList->state = LIST_OOB_START;
        return NULL;
    }
    return pList->curr->item;
}

void* List_curr(List* pList){
    return pList->curr->item;
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
        //printf("(case 0)");
        pList->head = pList->tail = pList->curr = added;
       // pList->head->next = pList->tail->next = pList->curr->next = NULL;
        return LIST_SUCCESS;
    }
    // case 1: curr befor head
    if(pList->curr == NULL && (pList->state == LIST_OOB_START)){
        //printf("(case 1)");
        return List_prepend(pList, pItem);
    }
    // case 2: curr beyond the end
    if(pList->curr == NULL && (pList->state == LIST_OOB_END)){
        //printf("(case 2)");
        return List_append(pList, pItem);
    }
    // case 3: curr @inside of pList
    //printf("(case 3)");
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
    if(pList->curr == NULL && (pList->state == LIST_OOB_START)){
        return List_prepend(pList, pItem);
    }
    // case 2: curr beyond the end
    if(pList->curr == NULL && (pList->state == LIST_OOB_END)){
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
    if(isEmpty(pList) || (pList->curr == NULL 
                        && ((pList->state ==  LIST_OOB_START) || (pList->state == LIST_OOB_END)))){
        return NULL;
    }
    pList->count--;
    void* r = pList->curr->item;
    int poolIndex = pList->curr->poolIndex;
    // case 0: one node, curr is head
    if(pList->curr == pList->head){
        pList->head->item = NULL;
        pList->curr->item = NULL;
    }
    // case 1: curr is tail
    else if(pList->curr == pList->tail){
        pList->curr = pList->curr->next; // set curr to NULL
        pList->tail = pList->tail->prev;
        pList->tail->next = NULL;
    }
    // case 2: inside
    else{
        Node* tmpNode = pList->curr;
        pList->curr->prev->next = pList->curr->next;
        pList->curr->next->prev = pList->curr->prev;
        pList->curr = pList->curr->next;
        tmpNode->item = r; 
    }
    stackPush(&nodeStack, poolIndex);
    nodeCount--;
    return r;
}

void* List_trim(List* pList){
    if(isEmpty(pList)){
        return NULL;
    }
    void* r = pList->tail->item;
    int poolIndex = pList->tail->poolIndex;
    // case 1: if one node list
    if(pList->count == 1){
        pList->state = LIST_OOB_END;
        pList->head = pList->curr = pList->tail = NULL;
    }
    else{
        pList->tail = pList->tail->prev; 
        if (pList->tail) { 
            pList->tail->next = NULL;
        }
        pList->curr = pList->tail; 
    }
    pList->count--;
    stackPush(&nodeStack, poolIndex);
    nodeCount--;
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
    pList2->count = 0;
    pList2->listsIndex = -1;
    stackPush(&stack, pList2->listsIndex);
}

void List_free(List* pList, FREE_FN pItemFreeFn){
    if(pList == NULL) return;
    Node* node = pList->head;
    while(node != NULL){
        Node* nextNode = node->next; 
        if(pItemFreeFn != NULL && node->item != NULL){
            (*pItemFreeFn)(node->item); 
        }
        free(node); 
        node = nextNode; 
    }

    pList->head = NULL;
    pList->curr = NULL;
    pList->tail = NULL;
    pList->count = 0;
    stackPush(&stack, pList->listsIndex); 
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

