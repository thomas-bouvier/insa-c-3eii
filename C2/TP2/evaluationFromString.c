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

Map_element elements[] = {{'+', add}, {'-', substract}, {'*', multiply}, {'/', divide}, {'s', square_root}, {'c', cube}};

int isANumber(char c) {
    return (c>='0') && (c <= '9');
}

/*!
* Handle a stack to evaluate a postfix expression
* \param[in] str the postfix expression to be evaluated
* \return int the result of the evaluation
*/
int evaluateExpression(char * str) {
  Stack s;
  int i;

  init_stack(&s);

  i = 0;
  while(str[i] != '\0') {
    if (isANumber(str[i]))
      push(&s, str[i] - '0');
    else {
      switch(str[i]) {
        case '+':
          add(&s);
          break;
        case '-':
          substract(&s);
          break;
        case '*':
          multiply(&s);
          break;
        case '/':
          divide(&s);
          break;
        default:
          fprintf(stderr, "Unknown operator\n");
          return 0;
      }
    }
    ++i;
  }
  return pop(&s);
}

int evaluateExpression_pf(char * str) {
  Stack s;
  int i;
  int j;
  Boolean found_operator;

  init_stack(&s);

  i = 0;
  j = 0;
  while(str[i] != '\0') {
    if (isANumber(str[i]))
      push(&s, str[i] - '0');
    else {
      int size = sizeof(elements) / sizeof(Map_element);
      found_operator = FALSE;
      for (j = 0; j < size; ++j) {
        if (elements[j].c == str[i]) {
          (*elements[j].act)(&s);
          found_operator = TRUE;
        }
      }
      if (found_operator == FALSE) {
        fprintf(stderr, "Unknown operator\n");
        return 0;
      }
    }
    ++i;
  }
  return pop(&s);
}

/*!
 * \fn int main_eval_string(void)
 * Tests stack functionnalities
 * \return EXIT_SUCCESS if everything is ok
 */
int main_eval_string(void) {
    Stack s;
    char * expr1 = "393-4*3/+";
    char * expr2 = "5393-4*3/++sc";

    init_stack(&s);
    printf("Evaluation of %s  (should be 11): %d\n", expr1, evaluateExpression_pf(expr1));
    printf("Evaluation of %s  (should be 64): %d\n", expr2, evaluateExpression_pf(expr2));

    return(EXIT_SUCCESS);
}
