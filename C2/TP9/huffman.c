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
            printf("==================================\n");
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

int readProbaFromFile(char * name, float pb[NBVALUES], int verbose) {
    FILE * f = NULL;
    short int buffer;
    int nbInstances[NBVALUES] = {0};
    int i;

    if ((f = fopen(name, "rb")) == (FILE *) NULL) {
        fprintf(stderr, "Error while opening file %s\n", name);
        return 0;
    }

    i = 0;
    while (1) {
        fread(&buffer, sizeof(short int), 1, f);
        if (buffer >= 0 && buffer < NBVALUES)
            ++nbInstances[buffer];

        if (verbose)
            printf("buffer: %d (nb %d)\n", buffer, i);

        if (feof(f))
            break;

        ++i;
    }
    printf("test");
    fclose(f);

    printf("close");

    for (i = 0; i < NBVALUES; ++i)
        pb[i] = ((float) nbInstances[i]) / ((float) 64 * 64);

    return 1;
}
