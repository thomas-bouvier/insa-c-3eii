/*!
 * \file    evaluation.h
 * \brief   Declaration of functions to process a stack of int as a post-fix expression
 */

#ifndef EVALUATION
#define EVALUATION

#include "application.h"
#include "stack.h"

Boolean add(Stack * s);
Boolean substract(Stack * s);
Boolean multiply(Stack * s);
Boolean divide(Stack * s);

int add_pf(int a, int b);
int substract_pf(int a, int b);
int multiply_pf(int a, int b);
int divide_pf(int a, int b);

/*int evaluateExpression(char *str);*/

int main_eval(void);

#endif
