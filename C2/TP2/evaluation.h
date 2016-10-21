/*!
 * \file    evaluation.h
 * \brief   Declaration of functions to process a stack of int as a post-fix expression
 */

#ifndef EVALUATION
#define EVALUATION

#include "application.h"
#include "stack.h"

typedef struct {
  char c;
  Boolean (*act) (Stack *);
} Map_element;

Boolean add(Stack * s);
Boolean substract(Stack * s);
Boolean multiply(Stack * s);
Boolean divide(Stack * s);

int add_pf(int a, int b);
int substract_pf(int a, int b);
int multiply_pf(int a, int b);
int divide_pf(int a, int b);

Boolean binary_operator_pf(Stack * s, int (*op) (int, int));

int evaluateExpression(char * str);
int evaluateExpression_pf(char * str);

int main_eval(void);
int main_eval_string(void);

#endif
