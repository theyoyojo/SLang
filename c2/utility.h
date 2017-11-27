#ifndef UTILITY_H
#define UTILITY_H "utility.h"

/*
 * Specification for general utility library
 *
 * [PURPOSE]
 *
 * Provide access to commonly used miscelaneous functions
 *
 * [INDEX]
 *
 * Library Prefix [Util] (Utility library)
 *
 * (_get_ operations)
 *
 * 1. safeRealloc(void*,long unsigned int)
 *      Takes a pointer and a size, attempts to allocate space to the extent of the
 *      speficied size
 *
 * (other)
 * 
 * 1. enum bool
 *      Create a bool type that represents underlying integer values for convenience
 * */

// [DECLERATIONS]

// (_get_ operations)

// 1. Resize the space allocated to a pointer given a new size
void * Util_get_safeRealloc(void * ptr, unsigned long int newSize);

// (other)

// 1. Bool type for convenience
typedef enum bool{false,true} bool;

#endif
