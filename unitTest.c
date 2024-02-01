#include "list.h"
//#include "list.c"

static void ListStatus(List* pList){
    printf("=================\n");
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
    printf("=================\n\n");
}

static void printList(List* pList){
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

int main(){
    List* list1 = List_create();
    //printList(pList);

    //-------------------------------------------------
    // List_insert_after: List_append, List_prepend
        printf("///////////////////////////////\n");
        printf("/////[ LIST_INSERT_AFTER ]/////\n");
        printf("///////////////////////////////\n\n");
    //-------------------------------------------------
    int size = 10;
    int itemArr1[size];
    for(int i = 0; i < size; i++){
        itemArr1[i] = i+size;
    }

    for(int i = 0; i < size; i++){
        int* item = &itemArr1[i];
        int a = List_insert_after(list1, (void*)item);
        if(a == LIST_SUCCESS) // max 100
            printList(list1);
    }

    ListStatus(list1);

    //-------------------------------------------------
    // List_insert_before: List_append, List_prepend
        printf("///////////////////////////////\n");
        printf("/////[ LIST_INSERT_BEFORE ]/////\n");
        printf("///////////////////////////////\n\n");
    //-------------------------------------------------
    int itemArr2[size];
    for(int i = 0; i < size; i++){
        itemArr2[i] = i;
    }
    for(int i = 0; i < size; i++){
        int* item = &itemArr2[i];
        int a = List_insert_before(list1, (void*)item);
        if(a == LIST_SUCCESS) // max 100
            printList(list1);
    }
    ListStatus(list1);

    //-------------------------------------------------
    // List_first
        printf("///////////////////////////////\n");
        printf("/////////[ LIST_FIRST ]////////\n");
        printf("///////////////////////////////\n\n");
    //-------------------------------------------------
    int* f1 = (int*)List_first(list1);
    printf("\nList_first: %d", *f1);
    ListStatus(list1);
    printList(list1);

    // empty list case
    List* list_empty = List_create();
    void* f_e = List_first(list_empty);
    if(f_e == NULL)
        printf("\nSuccess list_first of empty case");
    else
        printf("\nFail list_first of empty case");
    printList(list_empty);
    printList(list1);
    ListStatus(list_empty);

    //-------------------------------------------------
    // List_last
        printf("///////////////////////////////\n");
        printf("/////////[ LIST_LAST ]/////////\n");
        printf("///////////////////////////////\n\n");
    //-------------------------------------------------
    int* l1 = (int*)List_last(list1);
    printf("\nList_last: %d", *l1);
    ListStatus(list1);
    printList(list1);

    void* l_e = List_last(list_empty);
    if(l_e == NULL)
        printf("\nSuccess list_last of empty case");
    else
        printf("\nFail list_last of empty case");
    printList(list_empty);
    printList(list1);
    ListStatus(list_empty);

    //-------------------------------------------------
    // List_remove
        printf("///////////////////////////////\n");
        printf("////////[ LIST_REMOVE ]////////\n");
        printf("///////////////////////////////\n\n");
    //-------------------------------------------------
    for(int i = 0; i < 5; i++){
        int* rm = (int*)List_remove(list1);
        printf("removed: %d", *rm);
        printList(list1);
        ListStatus(list1);
    }


    //-------------------------------------------------
    // List_next
        printf("///////////////////////////////\n");
        printf("/////////[ LIST_NEXT ]/////////\n");
        printf("///////////////////////////////\n\n");
    //-------------------------------------------------
    
    for(int i = 0; (i < 5); i++){
        void* n = List_next(list1);
        ListStatus(list1);
    }
    // void* n = List_next(list1);
    // ListStatus(list1);
    // printList(list1);


    //-------------------------------------------------
    // List_prev
        printf("///////////////////////////////\n");
        printf("/////////[ LIST_PREV ]/////////\n");
        printf("///////////////////////////////\n\n");
    //-------------------------------------------------
    for(int i = 0; i < 3; i++){
        void* p = List_prev(list1);
        ListStatus(list1);
        printList(list1);
    }

    //-------------------------------------------------
    // List_curr
        printf("///////////////////////////////\n");
        printf("/////////[ LIST_CURR ]/////////\n");
        printf("///////////////////////////////\n\n");
    //-------------------------------------------------

    int* c = (int*)List_curr(list1);
    printf("curr item: %d", *c);
    ListStatus(list1);
    printList(list1);


    //-------------------------------------------------
    // List_trim
        printf("\n///////////////////////////////\n");
        printf("/////////[ LIST_TRIM ]/////////\n");
        printf("///////////////////////////////\n");
    //-------------------------------------------------
    // trim test #1: common case
    printf("[ TRIM TEST #1: common case]\n");
    printList(list1);
    int* tr = (int*)List_trim(list1);
    printList(list1);
    printf("trimed item: %d", *tr);
    ListStatus(list1);


    // trim test #2: one node list case
    printf("[ TRIM TEST #2: one node linked list trimming]\n");
    List* list2 = List_create();
    int z = 999;
    int* zz = &z;
    int zzz = List_insert_after(list2, (void*)zz);
    printList(list2);
    int* tr2 = (int*)List_trim(list2);
    printList(list2);
    printf("trimed item: %d", *tr);
    ListStatus(list2);

    // trim test #3: empty list
    printf("[ TRIM TEST #3:empty list]\n");
    tr = List_trim(list_empty);
    if(tr == NULL) printf("SUCCESS: Trim empty List");
    else printf("FAIL: Trim empty List");



    //-------------------------------------------------
    // List_concat
        printf("\n///////////////////////////////\n");
        printf("/////////[ LIST_CONCAT ]/////////\n");
        printf("///////////////////////////////\n");
    //-------------------------------------------------
    // concat test #1: common case
    printf("[ CONCAT TEST #1: common case]");
    List* list3 = List_create();
    List* list4 = List_create();
    for(int i = 0; i < size; i++){
        int* item1 = &itemArr1[i];
        int* item2 = &itemArr2[i];
        int p = List_insert_after(list3, (void*)item1);
        int q = List_insert_after(list4, (void*)item2);
    }
    printf("\nList a:");
    printList(list4);
    printf("List b:");
    printList(list3);
    List_concat(list4, list3);
    printf("After Concat\nList a:");
    printList(list4);
    printf("List b:");
    printList(list3);
    ListStatus(list3);   // list 4 exits and list3 not

    // concat test #2: either is empty
    printf("[ CONCAT TEST #2: Either one is empty]");
    printf("\nList c:");
    printList(list4);
    printf("List d:");
    printList(list_empty);
    List_concat(list4, list_empty);
    printList(list4);
    

    //-------------------------------------------------
    // List_free
        printf("\n///////////////////////////////\n");
        printf("/////////[ LIST_FREE ]/////////\n");
        printf("///////////////////////////////\n");
    //-------------------------------------------------
    


    return 0;
}