
/*!
* \file list.h
* \brief File defining the list structure as studied in Huffman coding practical work
*/

#ifndef LIST_H
#define LIST_H

#include "binary_tree.h"

/*!
* \brief Data element of a list, containing a tree
*/
typedef struct NodeList {
	 NodeTree * t;              /*!< A pointer to a tree*/
	 struct NodeList * next;    /*!< A pointer to the next element in the list*/
} NodeList;

/*!
* \brief list of tree nodes
*/
typedef struct {
	 NodeList * first; 			/*!< A pointer to the first list element*/
	 NodeList * current; 		/*!< A pointer to the current list element*/
	 NodeList * last; 			/*!< A pointer to the last list element*/
} List;

NodeList * newNodeList(NodeTree * t, NodeList * n);
void deleteNodeList(NodeList * n);

void initList(List * l);
void deleteList(List * l);

int empty(List * l);
int first(List * l);
int last(List * l);
int outOfList(List * l);

void setOnFirst(List * l);
void setOnLast(List * l);
void next (List * l);
NodeTree * getCurrentTree(List * l);

void printList(List * l);

int insertSort(List * l, NodeTree * p);

NodeTree * removeFirst(List * l);

#endif
