#include "list.h"
#include "list.c"

int main(){
    List* pList = List_create();
    //printList(pList);

    int pr1 = 1;
    void* p1 = &pr1;
    int a = List_insert_after(pList, p1);
    int* i = (int*)(pList->head->item);
    printf("%d \n", *i);
    //printf("%d \n", a);

    int pr2 = 2;
    void* p2 = &pr2;
    a = List_insert_after(pList, p2);
    i = (int*)(pList->head->item);
    printf("%d \n", *i);
    //printf("%d \n", a);
    printList(pList);

    return 0;
}