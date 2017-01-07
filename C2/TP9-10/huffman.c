#include "huffman.h"

int fillList(List * l, float pb[NBVALUES]) {
    int i;

    if (l != NULL) {
        for (i = 0; i < NBVALUES; ++i)
            insertSort(l, newNodeTree(pb[i], NULL, NULL));
    }

    return 0;
}

NodeTree * buildHuffmanTree(List * l) {
  int i = 1;
    NodeTree * subTree = NULL;

    if (l != NULL) {
        while (l->first != l->last) {
            printf("-----------------------------\n");
            printf("Step %d\n", i);

            if (l->first != NULL && l->last != NULL) {
                subTree = buildParentNode(l->first->t, l->first->next->t);

                removeFirst(l);
                removeFirst(l);

                insertSort(l, subTree);

                printList(l);
            }
            else
                return NULL;

            ++i;
        }
    }

    return subTree;
}

void huffmanTest() {
    List l;
    float probas[] = {0.01, 0.05, 0.07, 0.09, 0.11, 0.15, 0.22, 0.3};

    initList(&l);
    fillList(&l, probas);

    printList(&l);

    buildHuffmanTree(&l);
}
