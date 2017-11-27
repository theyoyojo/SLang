#ifndef STRING_H
#define STRING_H "string.h"

/*
 * Specification for String object.
 *
 * [PURPOSE]
 *
 * This library provides an abstract "string" type with many built-in operations. It allows for
 * strings, a tricky thing in c, to be contained and properly handled.
 *
 * [DATA]
 *
 * A string is an abstract sequence of 0 or more characters,
 *
 * The constituent characters of the string are guaranteed to be terminated by a null terminator
 * (char '\0' or int 0). This means that every string will have a minimum length of 1 character.
 *
 * The length value of the string object shall be the total number of characters in the string
 * *excluding* the null terminator. A length of zero indicates an implicit null temrinator.
 *
 * [INTERFACE]
 *
 * Object prefix: [Str] (String)
 *
 * */

// [CONSTANT DEFINITIONS] 

// The default maximum string size in characters
#define STR_DEFAULT_MAX_SIZE 128

// The ratio of newly initialized string length to total allocated memory for that string
#define STR_CAPACITY_MODIFIER 1.33333

// [HANDLE DECLERATION]
typedef void * String;

// [INTERFACE DECLERATIONS]

// (_init_ operations)

// Initialize an empty string of size defauly
String Str_init_default(void);

// Initialize a string with a specified max size
String Str_init_maxSize(int maxSize);

// Initialize a string with the value of a cstring literal constant
String Str_init_const(const char* string);

// (_free_ operations)

// Free all memory allocated to a String object. This kills the string
void Str_free(String str);

// (_edit_ operations)

// Add a string of 0 or greater characters to the end of a string
void Str_edit_append(String str, String add);

// Insert a string of 0 or greater characters into an existing string at an index, pushing contents forward
void Str_edit_insert(String str, String insert, int index);

// Insert a string of 0 or greater characters into an existing string at an index, overwriting existing contents 
void Str_edit_overwrite(String str, String insert, int index);

// Remove the contents of the string, leaving only the null terminator and a length of 0
void Str_edit_delete(String str);

// Delete the contents of a string within a certain defined index range and shift contents accordingly
void Str_edit_deleteRange(String str, int iBegin, int iEnd);

// (_get_ operations)

// Get the number of characters in the string before the null terminator
int Str_get_length(String str);

// Get the character in a string at an index. Returns '\0' if out of bounds
char Str_get_char(String str, int index);

// Get a pointer to a c string with the characters of the contained string data
const char* Str_get_string(String str);

// (_do_ operations)

// Print the string to a file
void Str_do_fprint(String str, FILE *fp);

// Print the string data to the screen
void Str_do_print(String str);

// Print the string to the screen with each character distinct and contained, include length
void Str_do_printDebug(String str);

#endif
