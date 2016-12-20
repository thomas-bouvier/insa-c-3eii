
/*!
* \file memoryList.h
* \brief File with the definition of a list of allocated blocks as studied in lab 7
*/
#ifndef MEMORYLIST_H
#define MEMORYLIST_H

/*!
* \brief the structure to store information about a memory block
*/
typedef struct {
    char * file;	        /*!< the filename where the memory has been allocated*/
    char * function;	    	/*!< the function name the memory has been allocated*/
    int line;		        /*!< the number of the line where the memory has been allocated*/
    void * address;	        /*!< the address of the allocated block*/
}MemoryBlock;

/*!
* \brief the data element type for the  list of allocated blocks
*/
typedef struct NodeList{
    MemoryBlock b;	/*!< information about the allocated block*/
    struct NodeList * next;	/*!< the address of the next element in the list*/
}NodeList;

/*!
* \brief the list type
*/
typedef struct{
    NodeList * first;       /*!< the address of the first element in the list*/
    NodeList * current;     /*!< the address of the current element in the list*/
    NodeList * last;        /*!< the address of the last element in the list*/
}List;



#endif
