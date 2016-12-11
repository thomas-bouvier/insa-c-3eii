/*!
* \file list.c
* \brief File with the functions required to manage the list as studied in labs 5 and 6
*/

#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "test.h"

/*!
* \brief  Unit testing of the functions provided in the list.c file
*/

/*group 1*/

static NodeList * newNodeList(int v, NodeList * n) {
    NodeList * new_node;

    new_node = (NodeList *) malloc(sizeof(NodeList));
    if (new_node == NULL) {
        fprintf(stderr, "Allocation error\n");
        exit(0);
    }

    new_node->val = v;
    new_node->next = n;

    return new_node;
}

static void freeNodeList(NodeList * n) {
    free(n);
}

/*group 2*/

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

int getCurrent(List * l) {
    if (!outOfList(l))
        return l->current->val;
    return 0;
}

/*group 3*/

void printList(List * l) {
    setOnFirst(l);

    while (!outOfList(l)) {
        printf("%d ", getCurrent(l));
        next(l);
    }

    printf("\n");
}

int insertFirst(List * l, int v) {
    NodeList * new_n = newNodeList(v, l->first);

    if (new_n == NULL)
        return 0;

    if (empty(l))
        l->last = new_n;

    l->first = new_n;

    return 1;
}

/*group 4*/

int deleteFirst(List * l, int * v) {
    NodeList * nToDel = l->first;

    if (!empty(l)) {
        if (v != NULL)
            *v = nToDel->val;

        l->first = l->first->next;
        setOnFirst(l);

        if (l->first == NULL)
            l->last = NULL;

        freeNodeList(nToDel);

        return 1;
    }

    return 0;
}

void freeList(List * l) {
    l = NULL;
}

/*group 5*/

int insertLast(List * l, int v) {
    NodeList * new_n = newNodeList(v, NULL);

    if (new_n == NULL)
        return 0;

    if (empty(l))
        l->first = l->last = new_n;
    else {
      l->last->next = new_n;
      l->last = new_n;
    }

    return 1;
}

int deleteLast(List * l, int * v) {
    NodeList * nToDel = l->last;
    NodeList * previous = NULL;

    if (!empty(l)) {
        if (v != NULL)
            *v = nToDel->val;

        setOnFirst(l);
        if (l->current == nToDel) {
          l->first = NULL;
        } else {
          while (!last(l)) {
            previous = l->current;
            next(l);
          }
          previous->next = NULL;
        }

        l->current = l->last = previous;

        if (l->last == NULL) {
          l->first = NULL;
        }

        freeNodeList(nToDel);
        return 1;
    }

    return 0;
}

void test_list() {
    int ret1,ret2;
    int val;

    List l1;
    List l2;

    /*TP4*/
    /*group 2*/

    initList(&l1);
    initList(&l2);

    display_test_int("Test empty() on an empty list", 1, empty(&l1));
    display_test_int("Test getCurrent() when the list is empty", 0, getCurrent(&l1));

    /*group 3*/

    display_test_check_by_user("Test printList on an empty list");
    printList(&l1);
    ret1 = insertFirst(&l1, 0);
    ret2 = insertFirst(&l1, 1);
    display_test_int("Test insertFirst() on an empty list", 1, ret1);
    display_test_int("Test insertFirst() on a not-empty list", 1, ret2);
    display_test_check_by_user("Test insertFirst : (list should be 1 0)");
    printList(&l1);

    display_test_int("Test empty() on a not-empty list", 0, empty(&l1));

    setOnLast(&l1);
    display_test_int("Test setOnLast()", 1, last(&l1));
    display_test_int("Test getCurrent() when in the list", 0, getCurrent(&l1));

    next(&l1);
    display_test_int("Test outOfList() when out of the list", 1, outOfList(&l1));
    display_test_int("Test getCurrent() when out of list", 0, getCurrent(&l1));

    setOnFirst(&l1);
    display_test_int("Test setOnFirst()", 1, first(&l1));
    next(&l1);
    display_test_int("Test outOfList() when in the list", 0, outOfList(&l1));

    /*group 4*/

    ret1 = deleteFirst(&l1, &val);
    display_test_int("Test deleteFirst() on a not-empty list", 1, ret1);
    display_test_int("Test deleteFirst() on a not-empty list", 1, val);
    display_test_check_by_user("Test deleteFirst : (list should be 0)");
    printList(&l1);

    ret1 = deleteFirst(&l1, NULL);
    display_test_check_by_user("Test deleteFirst with only an element in the list : (list should be empty)");
    printList(&l1);

    ret1 = deleteFirst(&l1, NULL);
    display_test_int("Test deleteFirst() on an empty list", 0, ret1);

    freeList(&l1);
    display_test_check_by_user("Test freeList on a not-empty list : (list should be empty)");
    printList(&l1);
    freeList(&l2);
    display_test_check_by_user("Test freeList on an empty list : (list should be empty)");
    printList(&l2);

    /*group 5*/

    ret1 = insertLast(&l2, 0);
    ret2 = insertLast(&l2, 1);
    display_test_int("Test insertLast() on an empty list", 1, ret1);
    display_test_int("Test insertLast() on a not-empty list", 1, ret2);
    display_test_check_by_user("Test insertLast : (list should be 0 1)");
    printList(&l2);

    ret1 = deleteLast(&l2, &val);
    display_test_int("Test deleteLast() on a not-empty list", 1, ret1);
    display_test_int("Test deleteLast() on a not-empty list", 1, val);
    display_test_check_by_user("Test deleteLast : (list should be 0)");
    printList(&l2);

    ret1 = deleteLast(&l2, NULL);
    display_test_check_by_user("Test deleteLast with only an element in the list : (list should be empty)");
    printList(&l2);

    ret1 = deleteLast(&l2, NULL);
    display_test_int("Test deleteLast() on an empty list", 0, ret1);

	  /*Always free the dynamically allocated memory*/

    freeList(&l1);
    freeList(&l2);
}
