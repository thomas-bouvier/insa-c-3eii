#include "binary_tree.h"

NodeTree * newNodeTree(float p, NodeTree * l, NodeTree * r) {
    NodeTree * new_node = NULL;

    if ((new_node = (NodeTree *) malloc(sizeof(NodeTree))) == (NodeTree *) NULL) {
        fprintf(stderr, "Allocation error\n");
        exit(0);
    }

    new_node->proba = p;
    new_node->left = l;
    new_node->right = r;

    return new_node;
}

void deleteNodeTree(NodeTree * n) {
    free(n);
}

NodeTree * buildParentNode(NodeTree * p1, NodeTree * p2) {
    if (p1 == NULL || p2 == NULL) {
        fprintf(stderr, "The provided NodeTree is NULL\n");
        return NULL;
    }

    return newNodeTree(p1->proba + p2->proba, p1, p2);
}

static int _print_t(Binary_tree t, int is_left, int offset, int depth, char s[20][255]) {
    char b[20];
    int width = 5;

    if (t == NULL) return 0;

    sprintf(b, "%5.3f", t->proba);

    int left  = _print_t(t->left,  1, offset,                depth + 1, s);
    int right = _print_t(t->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {
        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width / 2 + i] = '-';

        s[depth - 1][offset + left + width / 2] = '.';

    } else if (depth && !is_left) {
        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width / 2 + i] = '-';

        s[depth - 1][offset + left + width / 2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {
        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

    } else if (depth && !is_left) {
        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }
#endif

    return left + width + right;
}

static void print_t(Binary_tree t) {
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(t, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

void printTree(Binary_tree t) {
    print_t(t);
}

static void printCode(char cod[CODESIZEMAX], int size_code, float pb) {
    int i;

    printf("Codeword for probability %5.3f is: ", pb);
    for (i = 0; i < size_code; i++)
        printf(" %c", cod[i]);
    printf("\n");
}

static int isLeaf(Binary_tree t) {
    if (t == NULL)
        return 0;

    return t->left == NULL && t->right == NULL;
}

static void printCodewordsRec(Binary_tree t, char cod[CODESIZEMAX], int depth) {
  char cod_left[CODESIZEMAX];
  char cod_right[CODESIZEMAX];

    if (t != NULL) {
        strcpy(cod_left, cod);
        strcpy(cod_right, cod);

        cod_left[depth] = '0';
        cod_left[depth + 1] = '\0';
        cod_right[depth] = '1';
        cod_right[depth + 1] = '\0';

        printCodewordsRec(t->left, cod_left, depth + 1);

        if (isLeaf(t))
            printCode(cod, depth, t->proba);

        printCodewordsRec(t->right, cod_right, depth + 1);
    }
}

void printCodewords(Binary_tree t) {
    if (t == NULL) {
        fprintf(stderr, "The tree you are trying to print is NULL\n");
        return;
    }

    printCodewordsRec(t->left, "0", 1);
    printCodewordsRec(t->right, "1", 1);
}
