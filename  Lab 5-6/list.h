#ifndef LIST_H
#define LIST_H

typedef struct NodeList {
    int val;
    struct NodeList * next;
} NodeList;

typedef struct {
    NodeList * first;
    NodeList * current;
    NodeList * last;
} List;

/*group 2*/

void initList(List * l);
int empty(List * l);
int first(List * l);
int last(List * l);
int outOfList(List * l);
void setOnFirst(List * l);
void setOnLast(List * l);
void next(List * l);
int getCurrent(List * l);

/*group 3*/

void printList(List * l);
int insertFirst(List * l, int v);

/*group 4*/

int deleteFirst(List * l, int * v);
void freeList(List * n);

/*group 5*/

int insertLast(List * l, int v);
int deleteLast(List * l, int * v);

/*group 6*/

int insertAfterCurrent(List * l, int v);
int insertBeforeCurrent(List * l, int v);
int deleteCurrent(List * l, int * v);

int find(List * l, int v);
int deleteValue(List * l,  int v);

/*group 7*/

void sort(List * l);

void test_list();

#endif
