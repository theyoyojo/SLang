#ifndef UTILITY_H
#define UTILITY_H "utility.h"
#include "error.h"

typedef enum bool{false,true} bool;

typedef struct String {
	char* chars;
	int length;
} String;

typedef struct StringString {
	String* strings;
	int length;
} StringString;

String newString(int size);

StringString newStringString(int nStrings);

String promptForString(int max);

void safeRealloc(void **ptr, int newSize);

#endif
