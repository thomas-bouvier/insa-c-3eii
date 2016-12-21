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

/*!
* Initialize the list structure members to be consistent with an empty list.
* \param[out] l the list to be initialized
*/
void initList(List * l) {
    l->first = NULL;
    l->current = NULL;
    l->last = NULL;
}

/*!
* Test if it is an empty list.
* \param[in] l the list to be tested
* \return int 1 if empty, 0 otherwise
*/
int empty(List * l) {
    return l->first == NULL;
}

/*!
* Test if the current node is the first one.
* \param[in] l the list to be tested
* \return int if the current node is the first one, 0 otherwise
*/
int first(List * l) {
    return l->current == l->first;
}

/*!
* Test if the current node is the last one.
* \param[in] l the list to be tested
* \return int 1 if the current node is the last one, 0 otherwise
*/
int last(List * l) {
    return l->current == l->last;
}

/*!
* Test if the current node is not valid (ie NULL).
* \param[in] l the list to be tested
* \return int 1 if the current node is not valid, 0 otherwise
*/
int outOfList(List * l) {
    return l->current == NULL;
}

/*!
* Set the current node on the first one.
* \param[out] l the list to be modified
*/
void setOnFirst(List * l) {
    l->current = l->first;
}

/*!
* Set the current node on the last one.
* \param[out] l the list to be modified
*/
void setOnLast(List *l) {
    l->current = l->last;
}

/*!
* Set the current node on the next one.
* \param[out] l the list to be modified
*/
void next(List * l) {
    if (!outOfList(l))
        l->current = l->current->next;
}

/*!
* Retrieve the int value stored in the current element. If the current element is NULL, return 0.
* \param[in] l the list
* \return int the value of the current element if valid, 0 otherwise
*/
int getCurrent(List * l) {
    if (!outOfList(l))
        return l->current->val;
    return 0;
}

/*group 3*/

/*!
* Print the content of the list.
* \param[in] l the list to be displayed
*/
void printList(List * l) {
    setOnFirst(l);

    printf("List printing...\n");
    printf("\t");

    if (empty(l))
      printf("Empty list");

    while (!outOfList(l)) {
        printf("%d ", getCurrent(l));
        next(l);
    }

    printf("\n");
}

/*!
* Insert a new element containing the in value given as a parameter at the head of the list.
* \param[out] l the list
* \param[in] v the value to be inserted
* \return int 1 if the element was successfully inserted, 0 otherwise
*/
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

/*!
* Delete the first element of the list. Free the memory of the deleted list node.
* \param[out] l the list
* \param[in] v an address to store the deleted value. If null, no storage is performed.
* \return int 1 if the element was successfully deleted, 0 otherwise
*/
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

/*!
* Suppress all elements from the list.
* \param[out] l the list to be emptied
*/
void freeList(List * l) {
    NodeList * nToDel;
    setOnFirst(l);

    while (!outOfList(l)) {
        nToDel = l->current;
        next(l);
        freeNodeList(nToDel);
    }
}

/*group 5*/

/*!
* Insert a new element containing the int value given as a parameter at the tail of the list.
* \param[out] l the list
* \param[in] v the value to be inserted
* \return int 1 if the element was successfully inserted, 0 otherwise
*/
int insertLast(List * l, int v) {
    NodeList * new_n = newNodeList(v, NULL);

    if (new_n == NULL)
        return 0;

    if (empty(l))
        l->first = new_n;
    else
        l->last->next = new_n;

    l->last = new_n;

    return 1;
}

/*!
* Delete the last element of the list. Free the memory of the deleted list node.
* \param[out] l the list
* \param[in] v an address to store the deleted value. If null, no storage is performed.
* \return int 1 if the element was successfully deleted, 0 otherwise
*/
int deleteLast(List * l, int * v) {
    NodeList * nToDel = l->last;
    NodeList * previous = NULL;

    if (!empty(l)) {
        if (v)
            *v = nToDel->val;

        setOnFirst(l);
        if (l->current == nToDel)
          l->first = NULL;
        else {
          while (!last(l)) {
            previous = l->current;
            next(l);
          }
          previous->next = NULL;
        }

        l->current = l->last = previous;

        if (l->last == NULL)
          l->first = NULL;

        freeNodeList(nToDel);
        return 1;
    }

    return 0;
}

/*!
* Insert a new element containing the int value given as a parameter after the current element of the list.
* \param[out] l the list
* \param[in] v the value to be inserted
* \return int 1 if the element was successfully inserted, 0 otherwise
*/
int insertAfterCurrent(List * l, int v) {
    NodeList * new_n = NULL;

    if (!outOfList(l)) {
      new_n = newNodeList(v, l->current->next);

      l->current->next = new_n;

      if (l->current == l->last)
          l->last = l->current->next;

      return 1;
    }

    return 0;
}

/*!
* Insert a new element containing the int value given as a parameter before the current element of the list.
* \param[out] l the list
* \param[in] v the value to be inserted
* \return int 1 if the element was successfully inserted, 0 otherwise
*/
int insertBeforeCurrent(List * l, int v) {
  NodeList * new_n = NULL;
  NodeList * previous = NULL;
  NodeList * stop = NULL;

  if (!outOfList(l)) {
    new_n = newNodeList(v, l->current);
    stop = l->current;

    setOnFirst(l);
    while (l->current != stop) {
      previous = l->current;
      next(l);
    }

    if (l->current == l->first)
        insertFirst(l, v);
    else
        previous->next = new_n;

    return 1;
  }

  return 0;
}

/*!
* Delete the current element of the list. Free the memory of the delete list node.
* \param[out] l the list
* \param[out] v an address to store the deleted value. If null, no storage is performed.
* \return int 1 if the element was successfully deleted, 0 otherwise
*/
int deleteCurrent(List * l, int * v) {
  NodeList * previous = NULL;
  NodeList * stop = NULL;

    if (!outOfList(l)) {
      if (l->current == l->first)
          deleteFirst(l, v);
      else if (l->current == l->last)
          deleteLast(l, v);
      else {
          if (v)
              *v = l->current->val;

          stop = l->current;

          setOnFirst(l);
          while (l->current != stop) {
            previous = l->current;
            next(l);
          }

          previous->next = l->current->next;
          freeNodeList(l->current);
      }

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

    display_test_check_by_user("Test printList() on an empty list");
    printList(&l1);
    ret1 = insertFirst(&l1, 0);
    ret2 = insertFirst(&l1, 1);
    display_test_int("Test insertFirst() on an empty list", 1, ret1);
    display_test_int("Test insertFirst() on a not-empty list", 1, ret2);
    display_test_check_by_user("Test insertFirst() : (list should be 1 0)");
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
    display_test_check_by_user("Test deleteFirst() : (list should be 0)");
    printList(&l1);

    ret1 = deleteFirst(&l1, NULL);
    display_test_check_by_user("Test deleteFirst() with only an element in the list : (list should be empty)");
    printList(&l1);

    ret1 = deleteFirst(&l1, NULL);
    display_test_int("Test deleteFirst() on an empty list", 0, ret1);

    freeList(&l1);
    display_test_check_by_user("Test freeList() on a not-empty list : (list should be empty)");
    printList(&l1);
    freeList(&l2);
    display_test_check_by_user("Test freeList() on an empty list : (list should be empty)");
    printList(&l2);

    /*group 5*/

    ret1 = insertLast(&l2, 0);
    ret2 = insertLast(&l2, 1);
    display_test_int("Test insertLast() on an empty list", 1, ret1);
    display_test_int("Test insertLast() on a not-empty list", 1, ret2);
    display_test_check_by_user("Test insertLast() : (list should be 0 1)");
    printList(&l2);

    ret1 = deleteLast(&l2, &val);
    display_test_int("Test deleteLast() on a not-empty list", 1, ret1);
    display_test_int("Test deleteLast() on a not-empty list", 1, val);
    display_test_check_by_user("Test deleteLast() : (list should be 0)");
    printList(&l2);

    ret1 = deleteLast(&l2, NULL);
    display_test_check_by_user("Test deleteLast() with only an element in the list : (list should be empty)");
    printList(&l2);

    ret1 = deleteLast(&l2, NULL);
    display_test_int("Test deleteLast() on an empty list", 0, ret1);

    /*group 6*/
    // both lists are empty

    ret1 = insertAfterCurrent(&l1, 10);
    display_test_int("Test insertAfterCurrent() on an empty list", 0, ret1);

    insertLast(&l2, 0);
    insertLast(&l2, 2);
    insertLast(&l2, 4);
    insertLast(&l2, 6);
    setOnFirst(&l2);
    next(&l2);

    ret2 = insertAfterCurrent(&l2, 10);
    display_test_check_by_user("Test insertAfterCurrent() on a non-empty list : (list should be 0 2 10 4 6)");
    printList(&l2);

    setOnFirst(&l2);
    next(&l2);
    next(&l2);
    next(&l2);
    next(&l2);

    ret2 = insertAfterCurrent(&l2, 10);
    display_test_check_by_user("Test insertAfterCurrent() on a non-empty list : (list should be 0 2 10 4 6 10)");
    printList(&l2);

    ret1 = insertBeforeCurrent(&l1, 10);
    display_test_int("Test insertBeforeCurrent() on an empty list", 0, ret1);

    setOnFirst(&l2);
    next(&l2);

    ret2 = insertBeforeCurrent(&l2, 10);
    display_test_check_by_user("Test insertBeforeCurrent() on a non-empty list : (list should be 0 10 2 10 4 6 10)");
    printList(&l2);

    setOnFirst(&l2);

    ret2 = insertBeforeCurrent(&l2, 8);
    display_test_check_by_user("Test insertBeforeCurrent() on a non-empty list : (list should be 8 0 10 2 10 4 6 10)");
    printList(&l2);

    ret1 = deleteCurrent(&l1, NULL);
    display_test_int("Test deleteCurrent() on an empty list", 0, ret1);

    setOnFirst(&l2);
    next(&l2);
    next(&l2);
    next(&l2);
    next(&l2);
    next(&l2);

    ret2 = deleteCurrent(&l2, NULL);
    display_test_check_by_user("Test deleteCurrent() on a non-empty list : (list should be 8 0 10 2 10 6 10)");
    printList(&l2);

    setOnFirst(&l2);

    ret2 = deleteCurrent(&l2, NULL);
    display_test_check_by_user("Test deleteCurrent() on a non-empty list : (list should be 0 10 2 10 6 10)");
    printList(&l2);

    setOnFirst(&l2);
    next(&l2);
    next(&l2);
    next(&l2);
    next(&l2);
    next(&l2);

    ret2 = deleteCurrent(&l2, NULL);
    display_test_check_by_user("Test deleteCurrent() on a non-empty list : (list should be 0 10 2 10 6)");
    printList(&l2);

	  /*Always free the dynamically allocated memory*/

    freeList(&l1);
    freeList(&l2);
}
