#ifndef FILE_H
#define FILE_H "file.h"

/*
 * Specification for File utility library
 *
 * [PURPOSE]
 *
 * This library provides aditional functionality to the built-in FILE pointer type.
 * A program using this library will be able to perform (or attempt to perform) various
 * file operations on any supported platform. If support does not exist, the library
 * will default to generic alternatives
 *
 * Currently Supported:
 * Linux: TODO
 * Windows: TODO
 * MacOS: TODO
 * Solaris: TODO
 * OS/2: TODO
 * MS-DOS: TODO
 * TempleOS: TODO 
 *
 * [INDEX]
 *
 * Library Prefix: [File] (File operations library)
 *
 * (_get_ operations)
 *
 * 1. canRead(const char*)
 *      Check if the program can read a certain file
 *
 * 2. canWrite(const char*)
 *      Check if the program can write to a certain file
 *
 * 3. doesExist(const char*)
 *      Check if a certain file exists
 *
 * */

// [DECLERATIONS]

// (_get_ operations)

// 1. Check if the program has permissions to read a file
bool File_get_canRead(const char* filename);

// 2. Check if the program has permissions to write to a file
bool File_get_canWrite(const char* filename);

// 3. Check if a file exists on the disk
bool File_get_doesExist(const char* filename);


#endif
