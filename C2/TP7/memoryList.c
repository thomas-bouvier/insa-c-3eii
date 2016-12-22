
/*!
* \file memoryList.c
* \brief File with the functions required to manage the list of allocated blocks as studied in lab 7
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memoryList.h"

/*!
* \brief Free memory stored in a  MemoryBlock
* \param[in] b the address of the block structure to be freed.
*/
static void freeMemoryBlock(MemoryBlock * b) {
    if (b->file != NULL)
        free((void *) b->file);

    if (b->function != NULL)
        free((void *) b->function);

    b->file = b->function = NULL;
}

/*!
* \brief Initialize data for a memory block
* \param[in] b the address of the block structure to be initialized.
* \param[in] f the filename
* \param[in] fn the function name
* \param[in] l the line number
* \param[in] a the address of the allocated block
* \return MemoryBlock* the address of the initialised structure
*/
static MemoryBlock * initMemoryBlock(MemoryBlock * b, const char * f,  const char * fn, int l, void * a) {
    b->file = (char *) malloc(strlen(f) + 1);
    b->function = (char *) malloc(strlen(fn) + 1);

    if (b->file != NULL && b->function != NULL) {
        strcpy(b->file, f);
        strcpy(b->function, fn);
        b->line = l;
        b->address = a;
    }
    else
        freeMemoryBlock(b);

    return b;
}

static NodeList * newNodeList(const char * f, const char * fn, int l, void * a, NodeList * n) {
    NodeList * new_node = NULL;
    MemoryBlock memory_block;

    if ((new_node = (NodeList *) malloc(sizeof(NodeList))) == (NodeList *) NULL) {
        fprintf(stderr, "Allocation error\n");
        exit(0);
    }

    initMemoryBlock(&memory_block, f, fn, l, a);

    new_node->b = memory_block;
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

void freeList(List * l) {
    NodeList * nToDel;

    setOnFirst(l);
    while (!outOfList(l)) {
        nToDel = l->current;
        next(l);
        freeNodeList(nToDel);
    }

    l->first = l->current = l->last = NULL;
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

void setOnLast(List * l) {
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
    printf("List printing...\n");

    setOnFirst(l);
    while (!outOfList(l)) {
        printf("\tNode file: %s\n", l->current->b.file);
        printf("\tNode function: %s\n", l->current->b.function);
        printf("\tNode line: %d\n", l->current->b.line);
        printf("\n");

        next(l);
    }

    printf("\n");
}

int countElement(List * l) {
    int n = 0;

    setOnFirst(l);
    while (!outOfList(l)) {
        ++n;
        next(l);
    }

    return n;
}

int insertSort(List * l, const char * f, const char * fn, int ln, void * a) {
    NodeList * new_n = NULL;
    /*
    NodeList * previous_n = NULL;

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

    previous_n->next = new_n;
    return 1;
    */

    new_n = newNodeList(f, fn, ln, a, NULL);

    if (new_n == NULL)
        return 0;

    if (empty(l))
        l->first = new_n;
    else
        l->last->next = new_n;

    l->last = new_n;

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
    NodeList * previous = NULL;
    NodeList * stop = NULL;

    setOnFirst(l);
    while(!outOfList(l)) {
        if (a == l->current->b.address)
            stop = l->current;

        next(l);
    }

    if (stop) {
        setOnFirst(l);
        while (l->current != stop) {
            previous = l->current;
            next(l);
        }

        if (previous == NULL) {
            l->first = l->current->next;
        }
        else {
            previous->next = l->current->next;
        }

        freeNodeList(l->current);
        return a;
    }

    return NULL;
}
