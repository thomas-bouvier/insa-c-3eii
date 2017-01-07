#include "binary_tree.h"
#include "huffman.h"

int main() {
    /*
    NodeTree * node_1 = NULL;
    NodeTree * node_2 = NULL;
    NodeTree * node_3 = NULL;
    NodeTree * node_4 = NULL;
    NodeTree * node_5 = NULL;
    NodeTree * node_6 = NULL;
    NodeTree * node_7 = NULL;
    NodeTree * node_8 = NULL;
    NodeTree * node_9 = NULL;
    NodeTree * node_10 = NULL;
    NodeTree * node_11 = NULL;
    NodeTree * node_12 = NULL;
    NodeTree * node_13 = NULL;
    NodeTree * node_14 = NULL;
    NodeTree * node_15 = NULL;

    node_1 = newNodeTree(0.01, NULL, NULL);
    node_2 = newNodeTree(0.05, NULL, NULL);
    node_4 = newNodeTree(0.07, NULL, NULL);
    node_6 = newNodeTree(0.15, NULL, NULL);
    node_8 = newNodeTree(0.3, NULL, NULL);
    node_10 = newNodeTree(0.09, NULL, NULL);
    node_11 = newNodeTree(0.11, NULL, NULL);
    node_13 = newNodeTree(0.22, NULL, NULL);

    node_3 = buildParentNode(node_1, node_2);
    node_5 = buildParentNode(node_3, node_4);
    node_7 = buildParentNode(node_5, node_6);
    node_9 = buildParentNode(node_7, node_8);
    node_12 = buildParentNode(node_10, node_11);
    node_14 = buildParentNode(node_12, node_13);
    node_15 = buildParentNode(node_14, node_9);

    printTree(node_15);

    printCodewords(node_15);
    */

    List l1;
    List l2;
    List l3;

    printf("=======================================\n");
    printf("Huffman\n");
    printf("=======================================\n");

    float probas[] = {0.01, 0.05, 0.07, 0.09, 0.11, 0.15, 0.22, 0.3};

    initList(&l1);
    fillList(&l1, probas);

    printList(&l1);

    buildHuffmanTree(&l1);
    printCodewords(l1.first->t);

    printf("\n");
    printf("=======================================\n");
    printf("Huffman - IM1.IM\n");
    printf("=======================================\n");

    initList(&l2);
    fillList(&l2, readProbaFromFile("IM2.IM", probas, 1));

    return 0;
}
