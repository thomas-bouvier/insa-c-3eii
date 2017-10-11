#include <stdio.h>
#include <stdlib.h>

#include "myDoubleTree.h"

int main() {
    DTree t;
    double data_sorted[] = {1.0, 2.1, 3.5, 4.6, 5.1};
    double data2_unsorted[] = {2.1, 1.0, 3.5, 4.6, 5.1};
    int nb, nb2;
    int i;

    initTree(&t);

    nb = sizeof(data_sorted) / sizeof(data_sorted[0]);
    t = buildBalancedTreeFromSortedArray(data_sorted, nb);
    printTree(t);

    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    // testing getHeight()

    printf("hauteur : %d (should be 2)\n", getHeight(t));
    printf("hauteur : %d (should be 1)\n", getHeight(t->left));

    printf("max : %f (should be 5.1)\n", findMax(t));
    printf("max : %f (should be 2.1)\n", findMax(t->left));

    // testing removeNode()

    t = addDouble(t, 6);
    t = addDouble(t, 5.5);
    t = addDouble(t, 7);
    t = addDouble(t, 8);
    t = addDouble(t, 6.5);
    printTree(t);

    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    printf("\nRemoving 5.1\n");

    t = removeNode(t, 5.1);
    printTree(t);

    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    printf("\nRemoving 5.5\n");

    t = removeNode(t, 5.5);
    printTree(t);

    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    printf("\nAdding 5.6\n");

    t = addDouble(t, 5.6);
    printTree(t);

    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    printf("\nRight rotation\n");

    t = rightRotation(t);
    printTree(t);

    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    printf("\nLeft rotation\n");

    t = leftRotation(t);
    printTree(t);

    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    t = addDouble(t, 178);
    printTree(t);
    printf("\nBalance to AVL\n");

    t = reBalance(t);
    printTree(t);

    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    printTree(t);
    printf("Is the tree unbalanced ?\n%d\n", isUnbalancedTree(t));

    freeTree(t);

/*
    initTree(&t);

    nb = sizeof(data_unsorted)/sizeof(data_unsorted[0]);
    t = buildBalancedTreeFromSortedArray(data_unsorted, nb);
    printTree(t);
    freeTree(t);
*/
/*
    initTree(&t);
    t = readDTreeFromFile("data.bin");
    printTree(t);
*/
    freeTree(t);

    return 0;
}
