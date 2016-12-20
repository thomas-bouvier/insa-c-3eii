/*!
* \file list.c
* \brief File with the functions required to manage the list as studied in labs 5 and 6
*/

#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "test.h"

static MemoryBlock * initMemoryBlock(MemoryBlock * b, const char * f, const char * fn, int l, void * a) {

}

static void freeMemoryBlock(MemoryBlock * b) {

}

static NodeList * newNodeList(const char * f, const char * fn, int ln, void * a, NodeList * n) {
    NodeList * new_node;

    new_node = (NodeList *) malloc(sizeof(NodeList));
    if (new_node == NULL) {
        fprintf(stderr, "Allocation error\n");
        exit(0);
    }

    new_node->b.file = f;
    new_node->b.function = fn;
    new_node->b.line = ln;
    new_node->b.address = a;

    new_node->next = n;

    return new_node;
}

static void freeNodeList(NodeList * n) {
    free(n);
}

void initList(List * l) {
    l->first = NULL;
    l->current = NULL;
    l->last = NULL;
}

int empty(List * l) {
    return l->first == NULL;
}

int first(List * l) {
    return l->current == l->first;
}

int last(List * l) {
    return l->current == l->last;
}

int outOfList(List * l) {
    return l->current == NULL;
}

void setOnFirst(List * l) {
    l->current = l->first;
}

void setOnLast(List *l) {
    l->current = l->last;
}

void next(List * l) {
    if (!outOfList(l))
        l->current = l->current->next;
}

void * getCurrentAddress(List * l) {
    return l->current->b.address;
}

void printList(List * l) {
    setOnFirst(l);
    while (!outOfList(l)) {
        printf("%d ", getCurrent(l));
        next(l);
    }

    printf("\n");
}

int countElement(List * l) {
  int n = 0;

  while (!outOfList(l)) {
    ++n;
    next(l);
  }

  return n;
}

int insertSort(List * l, const char * f, const char * fn, int ln, void * a) {
    NodeList * new_n;
    NodeList * previous_n;

    setOnFirst(l);
    while (!outOfList(l) && strcmp(f, l->current->b.file) > 0) {
      previous_n = l->current;
      next(l);
    }

    new_n = newNodeList(f, fn, ln, a, l->current);

    if (new_n == NULL)
        return 0;

    if (empty(l)) {
      l->first = l->last = new_n;
      return 1;
    }

    previous_n->next = n;
    return 1;
}

int find(List * l, void * a) {
  setOnFirst(l);
  while(!outOfList(l) && (a == l->current->b.address)) {
    next(l);
  }

  return a == l->current->b.address;
}

void * deleteValue(List * l, void * a) {
  NodeList * previous_n;

  setOnFirst(l);
  while(!outOfList(l) && (a == l->current->b.address)) {
    previous_n = l->current;
    next(l);
  }

  if (a == l->current->b.address) {
    previous_n->next = l->current->next;
    freeNodeList(l->current);

    return a;
  }

  return NULL;
}
