/*! \file counter.c
*\brief Definitions for a counter structure
*/

#include "counter.h"
#include <stdlib.h>
#include <stdio.h>

/*!
\brief Allocate memory for a counter structure
\return counter * the address of the new counter
*/
counter * alloc_counter()
{
	return (counter *) malloc (sizeof(counter));
}

/*!
\brief Free memory associated to a counter structure
\param[in] p_c the address of the  counter to be deleted
*/
void free_counter(counter * p_c)
{
    if (p_c != NULL)
        free ((void *) p_c);
}

/*!
\brief Initialize a counter to 0
\param[in,out]  p_c the address of the  counter to be initialized
*/
void init_counter(counter * p_c)
{
	p_c->ms = 0;
}

/*!
\brief Add 1 to a counter
\param[in,out]  p_c the address of the  counter to be incremented
*/
void inc_counter(counter * p_c)
{
	p_c->ms++;
}


/*!
\brief Substract 1 to a counter
\param[in,out]  p_c the address of the  counter to be decreased
*/
void dec_counter(counter * p_c)
{
    if(p_c->ms >= 1)
        p_c->ms--;
    else
        fprintf(stderr, "Can not decrease the counter value\n");
}

/*!
\brief Get the counter value
\param[in,out]  p_c the address of the  counter
\return unsigned int the value of the counter
*/
unsigned int get_counter(counter * p_c)
{
	return p_c->ms;
}
