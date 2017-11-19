#ifndef ERROR_H
#define ERROR_H "error.h"

#define TOO_MANY_ARGS 0
#define REALLOC_FAIL 1
#define FILE_NOT_FOUND 2
#define BAD_FILE_READ 3
#define FILE_READ_ACCESS_DENIED 4
#define FILE_WRITE_ACCESS_DENIED 5

void throwException(int error);

void throwExceptionWithString(int error, const char* string);

#endif
