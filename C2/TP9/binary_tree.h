/*!
* \file binary_tree.h
* \brief File defining the binary Huffman tree structure as studied in Huffman coding practical work
*/

#ifndef BINARY_TREE_HH
#define BINARY_TREE_HH

/*! \def CODESIZEMAX
* \brief The maximal codeword length
*/
#define CODESIZEMAX 100

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/*!
* \brief Data element of a binary tree associated to a probability.
* If the left and right children are not null, its probability shall be equal to the sum of its children's probabilies.
*/
typedef struct NodeTree {
    float proba;                /*!< A pointer to a tree*/
    struct NodeTree * left;     /*!< A pointer to the left child, associated to the 0 bit*/
    struct NodeTree * right;    /*!< A pointer to the right child, associated to the 1 bit*/
} NodeTree;

/*!
*A tree is the top node
*/
typedef NodeTree * Binary_tree;

NodeTree * newNodeTree(float p, NodeTree * l, NodeTree * r);
void deleteNodeTree(NodeTree * n);

NodeTree * buildParentNode(NodeTree * l, NodeTree * r);

void printTree(Binary_tree t);
void printCodewords(Binary_tree t);

#endif
