#ifndef HUFFMAN_HH
#define HUFFMAN_HH

#include "list.h"
#include "binary_tree.h"

#define NBVALUES 8

int fillList(List * l, float pb[NBVALUES]);

NodeTree * buildHuffmanTree(List * l);

void huffmanTest();

#endif
