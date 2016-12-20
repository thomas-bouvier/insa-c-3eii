
/*!
* \file memoryList.c
* \brief File with the functions required to manage the list of allocated blocks as studied in lab 7
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoryList.h"

/*!
* \brief Initialize data for a memory block
* \param[in] b the address of the block structure to be initialized. 
* \param[in] f the filename
* \param[in] fn the function name
* \param[in] l the line number
* \param[in] a the address of the allocated block
* \return MemoryBlock* the address of the initialised structure
*/
static MemoryBlock * initMemoryBlock(MemoryBlock *b,const char *f,  const char * fn, int l, void * a)
{
        b->file = (char *)malloc(strlen(f)+1);
        b->function = (char *)malloc(strlen(fn)+1);
        if(b->file != NULL && b->function !=NULL)
        {
            strcpy(b->file,f);
            strcpy(b->function,fn);
            b->line = l;
            b->address = a;
        }
        else
	{
            freeMemoryBlock(b);
	}
       	    
    return b;
}


/*!
* \brief Free memory stored in a  MemoryBlock
* \param[in] b the address of the block structure to be freed. 
*/
static void freeMemoryBlock(MemoryBlock *b)
{
    if(b->file != NULL)
        free((void*) b->file);
    if(b->function != NULL)
        free((void*) b->function);
    
    b->file = b->function = NULL;
}


