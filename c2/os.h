/*
 * Cross-platform compatability header file
 *
 * */

// Enumerated OS keywords

#define OS_LINUX 1
#define OS_WINDOWS 2

// For Linux

#ifdef linux

#include <unistd.h>
#include <termios.h>

#ifndef OS
#define OS OS_LINUX
#endif

#ifndef OS_NAME
#define OS_NAME "linux"
#endif

#endif

// For Windows

#ifdef _WIN32

#include <windows.h>
#include <tchar.h>

#ifndef OS
#define OS OS_WINDOWS
#endif

#ifndef OS_NAME
#define OS_NAME "windows"
#endif


#endif
