#include "list.h"
#include "list.c"

int main(){
    List* list1 = List_create();
    //printList(pList);

    //-------------------------------------------------
    // List_insert_after: List_append, List_prepend
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
        printf("\n[ LIST_REMOVE ]---------------------------------------------------\n");
    //-------------------------------------------------
    for(int i = 0; i < 5; i++){
        int* rm = (int*)List_remove(list1);
        printf("removed: %d", *rm);
        printList(list1);
        ListStatus(list1);
    }


    //-------------------------------------------------
    // List_next
        printf("\n[ LIST_NEXT ]---------------------------------------------------\n");
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
        printf("\n[ LIST_PREV ]---------------------------------------------------\n");
    //-------------------------------------------------
    
    for(int i = 0; i < 3; i++){
        void* p = List_prev(list1);
        ListStatus(list1);
        printList(list1);
    }

    //-------------------------------------------------
    // List_curr
        printf("\n[ LIST_CURR ]---------------------------------------------------\n");
    //-------------------------------------------------
    int* c = (int*)List_curr(list1);
    printf("curr item: %d", *c);
    ListStatus(list1);



    return 0;
}