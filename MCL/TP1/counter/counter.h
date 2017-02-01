/*! \file counter.h
*\brief Declarations for a counter structure
*/
#ifndef COUNTER_H
#define COUNTER_H

typedef struct {
    unsigned int ms; /*!< The counter value. */
} counter;

counter * alloc_counter();
void free_counter(counter *);

void init_counter(counter * p_c);

void inc_counter(counter * p_c);
void dec_counter(counter * p_c);

unsigned int get_counter(counter * p_c);

#endif
