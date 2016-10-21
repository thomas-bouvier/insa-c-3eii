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

/*int evaluateExpression(char *str);*/

int main_eval(void);

#endif
