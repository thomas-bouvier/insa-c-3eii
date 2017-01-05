#ifndef MYDOUBLETREE_H_INC
#define MYDOUBLETREE_H_INC

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef struct DNode{
	double value;
	struct DNode * left;
	struct DNode * right;
} DNode;

typedef DNode * DTree;

/*provided*/
void initTree(DTree * t);
void freeTree(DTree t);

int isEmpty(DTree t);

int isLeaf(DTree t);

DTree addDouble(DTree  t, double v);

DTree buildBalancedTreeFromSortedArray(double * a, int n);

void printTree(DTree t);

int writeToFile(char * s, double *data, int nb);

/*to be done*/
DTree buildBalancedTreeFromUnsortedArray(double * a, int n);

int getHeight(DTree t);
int getBalance(DTree t);

DTree rightRotation(DTree t);
DTree leftRotation(DTree t);
DTree reBalance(DTree t);

double findMax(DTree t);
int isUnbalancedTree(DTree t);
DTree removeNode(DTree t, double value);

double * readArrayFromFile(char *s, int * nb);
DTree readDTreeFromFile(char *s);

#endif
