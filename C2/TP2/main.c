/*!
 * \file    main.c
 * \brief   main program
 *
 * \author ...
 * \date ...
 */

#include <stdio.h>

#include "application.h"
#include "stack.h"
#include "evaluation.h"

/*!
 * \fn int main(void)
 * \return EXIT_SUCCESS if everything is ok
 */
int main(void) {
    /*return main_stack();*/
    /*return main_eval();*/
    return main_eval_string();

    return 0;
}
