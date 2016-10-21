/*!
 * \file  stack.c
 * \brief Declaration of the functions required to handle a stack of int and int operators
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "stack.h"

/*!
 * Initialize the stack
 * \param[in] s the stack to be initialized
 */
void init_stack(Stack * s) {
    s->top = INIT_TOP;
}

/*!
 * Empty the stack
 * \param[in] s the stack to be deleted
 */
void delete_stack(Stack * s) {
    init_stack(s);
}

/*!
 * Fill the stack
 * \param[in] s the stack to be filled
 * \param[in] n_element the number of elements to push
 * \param[in] ... the elements to be pushed
 */
int fill_stack(Stack * s, int n_element, ...) {
  int i;
  va_list l;

  va_start(l, n_element);

  for (i = 0; i < n_element; ++i)
    push(s, va_arg(l, int));
  va_end(l);

  return 0;
}

/*!
 * Tests if the stack is empty
 * \param[in] s the stack to be tested
 * \return Booelan TRUE if empty, FALSE otherwise
 */
Boolean isEmpty(Stack * s) {
    return (s->top == INIT_TOP)? TRUE : FALSE;
}

/*!
 * Tests if the stack is full
 * \param[in] s the stack to be tested
 * \return Booelan TRUE if full  FALSE otherwise
 */
Boolean isFull(Stack * s) {
    return (s->top == STACK_MAX_SIZE -1)? TRUE : FALSE;
}

/*!
 * Add a value at the top of the stack
 * \param[out] s the stack to be modified
 * \param[in] value the value to be added
 * \return int 1 if everything was OK, 0 otherwise
 */
int push(Stack * s, int value) {
    if ((s != NULL)) {
        if ((isFull(s) == FALSE)) {
            ++(s->top);
            s->data[s->top] = value;
            return 1;
        }
        fprintf(stderr, "Can not push a value : full stack (overflow)\n");
        return 0;
    }
    fprintf(stderr, "Can not push a value :  stack is null\n");
    return 0;
}

/*!
 * Remove the top value  of the stack
 * \param[out] s the stack to be modified
 * \return int the value to be removed. Returns 0 if an error occurs.
 */
int pop(Stack * s) {
    if ((s != NULL)) {
        if ((isEmpty(s) == FALSE)) {
            --(s->top);
            return s->data[s->top + 1];
        }
        fprintf(stderr, "Can not pop a value : empty stack\n");
        return 0;
    }
    fprintf(stderr, "Can not pop a value :  stack is null\n");
    return 0;
}

/*!
 * Display the stack content
 * \param[int] s the stack to be printed
 */
void display_stack(Stack * s) {
  int i;
  printf("***** Stack content:\n");
  for (i = 0; i <= s->top; ++i)
    printf("\t%3d  %d\n", i, s->data[i]);
}

/*!
 * \fn int main_stack(void)
 * Tests stack functionnalities
 * \return EXIT_SUCCESS if everything is ok
 */
int main_stack(void) {
  Stack s;

  init_stack(&s);
  push(&s, 1);
  push(&s, 2);
  push(&s, 3);
  pop(&s);
  push(&s, 4);
  fill_stack(&s, 4, 1, 2, 3, 4);
  display_stack(&s);

  return(EXIT_SUCCESS);
}
