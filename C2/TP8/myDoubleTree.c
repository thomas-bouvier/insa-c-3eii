
#include "myDoubleTree.h"

#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*!
* \brief Allocate memory for the node element and initialize the structure members
* \param[in] v the double for the value member
* \param[in] l the address of the left child
* \param[in] r the address of the right child
* \return DNode* the address of the new tree element
*/
DNode * initNode(double v, DNode * l, DNode * r) {
    DNode * new = (DNode*) malloc(sizeof(DNode));

    if (new == NULL)
        return NULL;

    new->value = v;
    new->left = l;
    new->right = r;

    return new;
}

/*!
* \brief Desallocate memory associated to a node
* \param[in] n the address of the  data element to be freed
*/
static void freeNode(DNode * n) {
    free((void *) n);
}

/*!
* \brief Suppress all elements from a tree
* \param[in] t the tree to be emptied
*/
void freeTree(DTree t) {
    if (t != NULL) {
        if (t->right != NULL)
            freeTree(t->right);

        if (t->left != NULL)
            freeTree(t->left);

        freeNode(t);
    }
}

/*!
* \brief Initialize an empty tree
* \param[out] t the tree to be initialized
*/
void initTree(DTree * t) {
    *t = NULL;
}

static int balanceFactor(DTree t) {
    return getHeight(t->right) - getHeight(t->left);
}

/*!
* \brief Tests if it is an empty tree
* \param[in] t the tree to be tested
* \return int 1 if empty, 0 otherwise
*/
int isEmpty(DTree t) {
    return t == NULL;
}

/*!
* \brief Tests if it is a leaf
* \param[in] t the tree to be tested
* \return int 1 if it is a leaf, 0 otherwise
*/
int isLeaf(DTree t) {
    return t->left == NULL && t->right == NULL ;
}

/*!
* \brief Insert a new element containing the double value given as a parameter to get a sorted tree
* \param[in,out] t the tree
* \param[in] v the value to be inserted
* \return int 1 if everything was OK, 0 otherwise
*/
DTree addDouble(DTree t, double v) {
    if (isEmpty(t))
        t = initNode(v, NULL, NULL);
    else
    {
        double current_val = t->value;
        if (current_val == v)
            return t; /*already in the tree*/
        else
            if (current_val > v)
                t->left = addDouble(t->left, v);
            else
                t->right = addDouble(t->right, v);
    }
    return t;
}

/*!
* \brief Build a sorted tree from a sorted array
* \param[in] a the array of sorted values
* \param[in] n the number of values in the array
* \return DTree the new tree
*/
DTree buildBalancedTreeFromSortedArray(double * a, int n) {
    if(n != 0)
        return initNode(a[n / 2], buildBalancedTreeFromSortedArray(a, n / 2), buildBalancedTreeFromSortedArray(a + n / 2 + 1, (n - 1) / 2));
    return NULL;
}

/*!
* \brief Print the content of the current node of the tree
* \param[in] t the node to be displayed
* \param[in] depth its depth in the tree
*/
static void printTreeRec(DTree t, int depth) {
	if (!isEmpty(t)) {
        int i;
        printTreeRec(t->left, depth + 1);
        for (i = 0; i < depth ; i++)
            printf("\t");

        printf("%f\n", t->value);
        printTreeRec(t->right, depth + 1);
	}
}

/*!
* \brief Print the content of the tree
* \param[in] t the tree to be displayed
*/
void printTree(DTree t) {
	if (!isEmpty(t)) {
        printf("--------- Printing tree : --------- \n");
        printTreeRec(t, 0);
        printf("--------- End of printing tree --------- \n\n");
	}
	else
        printf("This tree is empty \n");
}

/*!
* \brief Retrieve the height of the tree
* \param[in] t the tree
*/
int getHeight(DTree t) {
    if (isEmpty(t) || isLeaf(t))
        return 0;

    return 1 + MAX(getHeight(t->left), getHeight(t->right));
}

/*!
* \brief Find the maximal value found in the tree
* \param[in] t the tree
*/
double findMax(DTree t) {
  if (isEmpty(t))
      return 0;

  while (!isEmpty(t->right))
      t = t->right;

  return t->value;
}

/*!
* \brief Remove a value from the tree
* \param[in] t the tree
* \param[in] value the value to remove
*/
DTree removeNode(DTree t, double value) {
    if (isEmpty(t)) {
        // empty tree or value not found; nothing to do
    } else if (t->value < value) {
        // value is in the right subtree, if it is in the tree at all ; go right
        t->right = removeNode(t->right, value);
    } else if (t->value > value) {
        // value is in the left subtree, if it is in the tree at all ; go left
        t->left = removeNode(t->left, value);
    } else {
        // t->value == value ; this node is the node to remove
        if (isLeaf(t)) {
            // case 1 : leaf
            freeNode(t);
            t = NULL;
        } else if (t->right == NULL) {
            // case 2 : left child only ; replace with left child
            t = t->left;
            freeNode(t->left);
            t->left = NULL;
        } else if (t->left == NULL) {
            // case 3 : right child only ; replace with right child
            t = t->right;
            freeNode(t->right);
            t->right = NULL;
        } else {
            // case 4 : both children ; replace with maximal value from left subtree
            double max = findMax(t->left);
            t->left = removeNode(t->left, max);
            t->value = max;
        }
    }

    return t;
}

/*!
* \brief Test if a tree is unbalanced
* \param[in] t the tree
* \return int 1 if unbalanced, 0 otherwise
*/
int isUnbalancedTree(DTree t) {
    return !isEmpty(t) && (isUnbalancedTree(t->left) || isUnbalancedTree(t->right) || (abs(balanceFactor(t)) > 1));
}

static DTree getParent(DTree t, double value) {
    if (isEmpty(t) || isLeaf(t) || t->value == value)
        return NULL;

    if (value < t->value){
        if (isEmpty(t->left))
            return NULL;

        if (t->left->value == value)
            return t;

        return getParent(t->left, value);
    } else {
        if (isEmpty(t->right))
            return NULL;

        if (t->right->value == value)
            return t;

        return getParent(t->right,value);
    }
}

/*!
* \brief Perform a right rotation
* \param[in] t the tree
* \return DTree the new tree
*/
DTree rightRotation(DTree t) {
    DTree q = t->left;
    t->left = q->right;
    q->right = t;

    return q;
}

/*!
* \brief Perform a left rotation
* \param[in] t the tree
* \return DTree the new tree
*/
DTree leftRotation(DTree t) {
    DTree q = t->right;
    t->right = q->left;
    q->left = t;

    return q;
}

/*!
* \brief Provide an AVL tree
* \param[in] t the tree
* \return DTree the new AVL tree
*/
DTree reBalance(DTree t) {
    if (isEmpty(t))
        return t;

    int balance = balanceFactor(t);
    if (balance > 1) {
        t = leftRotation(t);
    }
    if (balance < -1) {
        t = rightRotation(t);
    }

    t->right = reBalance(t->right);
    t->left = reBalance(t->left);

    return t;
}
