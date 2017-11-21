#ifdef linux

#include <unistd.h>
#include <termios.h>

#ifndef OS
#define OS "linux"
#endif

#endif

#ifdef _WIN32

#include <windows.h>
#include <tchar.h>

#ifndef OS
#define OS "windows"
#endif


#endif
