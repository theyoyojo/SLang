#ifndef UTILITY_H
#define UTILITY_H "utility.h"
#include "error.h"
#include <stdio.h>

#define KEY_ESC "\027"
#define KEY_UP "\027[A"
#define KEY_DOWN "\027[B"
#define KEY_RIGHT "\027[C"
#define KEY_LEFT "\027[D"

typedef enum bool{false,true} bool;

typedef struct String {
	char* chars;
	int length;
  int capacity;
} String;

typedef struct StringString {
	String* strings;
	int length;
  int capacity;
} StringString;

String newString(int size);

void printString(FILE *out, String string);

void appendString(String *s, const char* add);

void insertString(String *s, const char* insert, int index);

String constToString(const char* literal);

void killString(String *toKill);

StringString newStringString(int nStrings, String *strings);

//macro to newStringString()
StringString newSS(int nStrings, String *strings);

void appendStringString(StringString *ss, String *s);

//macro to appendStringString()
void appendSS(StringString *ss, String *s);

void insertStringString(StringString *ss, String *s, int index);

//macro to insertStringString()
void insertSS(StringString *ss, String *s, int index);

void killSS(StringString *toKill);

//macro to killSS()
void killStringString(StringString *toKill);

String promptForString(int max,const char* prompt);

void printSS(FILE *out, StringString ss);

//macro to printSS()
void printStringString(FILE *out, StringString ss);

StringString stringCharsToStringString(String str);

void * safeRealloc(void *ptr, unsigned long int newSize);

int getRawLine(FILE *in, char** buff, int buffSize);

bool getUserBool(const char* prompt);

bool isReadableFile(const char* filename);

bool isWritableFile(const char* filename);

bool fileExists(const char* filename);

#endif
