#include "list.h"
#include "list.c"

int main(){
    List* pList = List_create();
    //printList(pList);

    int pr1 = 11;
    void* p1 = &pr1;
    int a = List_insert_after(pList, p1);
    int* i = (int*)(pList->head->item);
    //printf("%d \n", *i);
    //printf("%d \n", a);

    int pr2 = 22;
    void* p2 = &pr2;
    a = List_insert_after(pList, p2);
    i = (int*)(pList->head->item);
    //printf("%d \n", *i);
    //printf("%d \n", a);
    printList(pList);

    int pr3 = 33;
    void* p3 = &pr3;
    a = List_insert_after(pList, p3);
    printList(pList);

    // List_count
    int c = List_count(pList);
    printf("\nThe # of nodes is %d \n", c);

    // List_first
    printf("\nFirst item: %d\n", *((int*)List_first(pList)));
    printList(pList);

    return 0;
}