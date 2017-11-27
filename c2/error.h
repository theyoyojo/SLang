#ifndef ERROR_H
#define ERROR_H "error.h"

/*
 * Specification for Error utility library
 *
 * [PURPOSE]
 *
 * This library provides a central index and location to process and handle errors of various types.
 *
 * [INDEX]
 *
 * Library Prefix: [Err] (Error messages)
 * 
 * (_do_ operations)
 *
 * 1. default(int)
 *     Takes an error code as defined below and outputs the appropriate message
 *
 * 2. string(int,const char*)
 *     Takes an error code as defined below and outputs the appropriate message
 *     with a relevant string indluded 
 *
 * */

// [CONSTANT DECLERATIONS]

// Too many arguments at the command line
#define TOO_MANY_ARGS 0

// Unable to reallocate memory for some purpose
#define REALLOC_FAIL 1

// A file was searched for by the program but not found
#define FILE_NOT_FOUND 2

// There was an error reading the file
#define BAD_FILE_READ 3

// Either the user or the program does not have permissions to read a file
#define FILE_READ_ACCESS_DENIED 4

// Either the user or the program deos not have permissions to write to a file
#define FILE_WRITE_ACCESS_DENIED 5

// An operation is not supported on a certain operating system
#define OS_NOT_IMPLEMENTED 6

// [DECLERATIONS]

// (_do_ operations)

// 1. Print an error message that corresponds to an error code
void Err_do_default(int error);

// 2. Print an error message that corresponds to an error code with a string
void Err_do_string(int error, const char* string);

#endif
