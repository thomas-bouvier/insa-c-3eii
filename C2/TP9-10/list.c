#include <stdlib.h>
#include <stdio.h>

#include "list.h"

NodeList * newNodeList(NodeTree * t, NodeList * n) {
    NodeList * new_node = (NodeList *) malloc(sizeof(NodeList));

    if (new_node == NULL) {
        fprintf(stderr, "Allocation error\n");
        exit(0);
    }

    new_node->t = t;
    new_node->next = n;

    return new_node;
}

void deleteNodeList(NodeList * n) {
    free(n);
}

void initList(List * l) {
    l->first = NULL;
    l->current = NULL;
    l->last = NULL;
}

void deleteList(List * l) {
    NodeList * nToDel = NULL;

    setOnFirst(l);
    while (!outOfList(l)) {
        nToDel = l->current;
        next(l);
        deleteNodeList(nToDel);
    }

    initList(l);
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

NodeTree * getCurrentTree(List * l) {
    if (!outOfList(l))
        return l->current->t;

    return 0;
}

void printList(List * l) {
    setOnFirst(l);

    printf("List printing...\n");

    if (empty(l))
      printf("Empty list");

    while (!outOfList(l)) {
        printTree(getCurrentTree(l));
        next(l);
    }

    printf("\n");
}

int insertSort(List * l, NodeTree * t) {
    NodeList * new_n = NULL;
    NodeList * previous = NULL;

    if (empty(l)) {
        new_n = newNodeList(t, l->first);

        if (new_n == NULL)
            return 0;

        l->first = l->current = l->last = new_n;
    } else {
        setOnFirst(l);
        while (!outOfList(l) && t->proba > l->current->t->proba) {
            previous = l->current;
            next(l);
        }

        new_n = newNodeList(t, l->current);

        if (new_n == NULL)
            return 0;

        if (previous)
            previous->next = new_n;
        else
            l->first = new_n;

        if (previous == l->last)
            l->last = new_n;
    }

    return 1;
}

NodeTree * removeFirst(List * l) {
    NodeTree * first = l->first->t;
    l->first = l->first->next;
    return first;
}
