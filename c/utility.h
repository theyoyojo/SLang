#ifndef UTILITY_H
#define UTILITY_H "utility.h"
#include "error.h"
#include <stdio.h>

typedef enum bool{false,true} bool;

typedef struct String {
	char* chars;
	int length;
  int capacity;
} String;

typedef struct StringString {
	String* strings;
	int length;
} StringString;

String newString(int size);

StringString newStringString(int nStrings, String *strings);

String promptForString(int max);

void printSS(StringString ss);

StringString stringCharsToStringString(String str);

void * safeRealloc(void *ptr, int newSize);

int getRawLine(FILE *in, char** buff, int buffSize);

#endif
