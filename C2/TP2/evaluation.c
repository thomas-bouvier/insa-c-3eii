/*!
 * \file  evaluation.c
 * \brief  Definition of functions to process a stack of int as a post-fix expression
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "application.h"
#include "evaluation.h"
#include "stack.h"

static Boolean binary_operator(Stack * s, int operation) {
  int op1, op2; /* the operands */
  int res; /* the result */

  if (isEmpty(s)) {
    fprintf(stderr, "Empty stack: can not proceed to the binary operation\n");
    return(FALSE);
  }
  op1 = pop(s);

  if (isEmpty(s)) {
    fprintf(stderr, "Empty stack: can not proceed to the binary operation\n");
    return(FALSE);
  }
  op2 = pop(s);

  /* computation */
  switch (operation) {
    case ADD:
      res = op1 + op2;
      break;
    case SUBSTRACT:
      res = op2 - op1;
      break;
    case MULTIPLY:
      res = op1 * op2;
      break;
    case DIVIDE:
      res = op2 / op1;
      break;
    default:
      fprintf(stderr,"Unknown operator\n");
      return(FALSE);
  }

  /* Put the result in the stack */
  push(s, res);

  return(TRUE);
}

Boolean binary_operator_pf(Stack * s, int (*op) (int, int)) {
  int op1, op2; /* the operands */

  if (isEmpty(s)) {
    fprintf(stderr, "Empty stack: can not proceed to the binary operation\n");
    return(FALSE);
  }
  op1 = pop(s);

  if (isEmpty(s)) {
    fprintf(stderr, "Empty stack: can not proceed to the binary operation\n");
    return(FALSE);
  }
  op2 = pop(s);

  push(s, (*op)(op1, op2));

  return(TRUE);
}

Boolean unary_operator_pf(Stack * s, int (*op) (int)) {
  int op1;

  if (isEmpty(s)) {
    fprintf(stderr, "Empty stack: can not proceed to the binary operation\n");
    return(FALSE);
  }
  op1 = pop(s);

  push(s, (*op)(op1));

  return(TRUE);
}

/*!
* Modify the stack state by adding its two first values
* \param[in,out] s the stack to be modified
* \return Booolean TRUE if the operation is successful, FALSE otherwise
*/
Boolean add(Stack * s) {
  return binary_operator_pf(s, add_pf);
  /* return binary_operator(s, ADD); */
}

/*!
* Modify the stack state by substracting its two first values
* \param[in,out] s the stack to be modified
* \return Booolean TRUE if the operation is successful, FALSE otherwise
*/
Boolean substract(Stack * s) {
  return binary_operator_pf(s, substract_pf);
  /* return binary_operator(s, SUBSTRACT); */
}

/*!
* Modify the stack state by multiplying its two first values
* \param[in,out] s the stack to be modified
* \return Booolean TRUE if the operation is successful, FALSE otherwise
*/
Boolean multiply(Stack * s) {
  return binary_operator_pf(s, multiply_pf);
  /* return binary_operator(s, MULTIPLY); */
}

/*!
* Modify the stack state by dividing its two first values
* \param[in,out] s the stack to be modified
* \return Booolean TRUE if the operation is successful, FALSE otherwise
*/
Boolean divide(Stack * s) {
  return binary_operator_pf(s, divide_pf);
  /* return binary_operator(s, DIVIDE); */
}

Boolean square_root(Stack * s) {
  return unary_operator_pf(s, square_root_pf);
}

Boolean cube(Stack * s) {
  return unary_operator_pf(s, cube_pf);
}

int add_pf(int a, int b) {
  return a + b;
}

int substract_pf(int a, int b) {
  return b - a;
}

int multiply_pf(int a, int b) {
  return a * b;
}

int divide_pf(int a, int b) {
  return b / a;
}

int square_root_pf(int a) {
  return sqrt(a);
}

int cube_pf(int a) {
  return a * a * a;
}

/*!
 * \fn int main_eval(void)
 * Tests stack functionnalities
 * \return EXIT_SUCCESS if everything is ok
 */
int main_eval(void){
  Stack s;

  init_stack(&s);

  /*
  push(&s, 1);
  push(&s, 2);
  substract(&s);
  push(&s, 3);
  add(&s);
  push(&s, 4);
  push(&s, 5);
  add(&s);
  add(&s);
  */

  push(&s, 3);
  push(&s, 9);
  push(&s, 3);
  substract(&s);
  push(&s, 4);
  multiply(&s);
  push(&s, 3);
  divide(&s);
  add(&s);

  printf("Result of this expression (should be 11): %d\n", pop(&s));

  return(0);
}
