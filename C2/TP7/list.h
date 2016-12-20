#ifndef LIST_H
#define LIST_H

typedef struct {
  char * file;
  char * function;
  int line;
  void * address;
} MemoryBlock;

typedef struct NodeList {
    MemoryBlock b;
    struct NodeList * next;
} NodeList;

typedef struct {
    NodeList * first;
    NodeList * current;
    NodeList * last;
} List;

void initList(List * l);

int empty(List * l);
int first(List * l);
int last(List * l);
int outOfList(List * l);

void setOnFirst(List * l);
void setOnLast(List * l);
void next(List * l);
void * getCurrentAddress(List * l);

void printList(List * l);
int countElement(List * l);

int insertSort(List * l, const char * f, const char * fn, int ln, void * a, NodeList * n);

int find(List * l, void * a);
void * deleteValue(List * l, void * a);

#endif
