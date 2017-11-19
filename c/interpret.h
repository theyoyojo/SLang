#ifndef INTERPRET_H
#define INTERPRET_H "interpret.h"
#include <stdlib.h>
#include <stdio.h>
#include "program.h"

//interpreter modes, interactive will prompt user for input, script will simply interpret a file
//interactive is default if no input file(s)
//script is default if there is a file unless -i or --interactive is specified
#define INTERACTIVE 0
#define SCRIPT 1

//TODO allow user to adjust buffer with args
#define DEFAULT_BUFFER_SIZE 1000


typedef struct Session
{
  //interpret vs script
  int mode;

  //cursor variables for parse of Program
  int program;  //The index in Program *file
  int line;     //The line of the program
  int symbol;   //The the index of the symbol in the line
  int chr;      //The index of the character in the symbol

  //A pointer to one or more active Program instances and a corresponding count
  //These are the scripts that are loaded into memmory
  Program *filev;
  int filec;

  //Points to the program currently being written to
  Program *active;
  
  //A pointer to a file object vector of all referenced files and a count of the number of ref
  //The file names are stored in refnames
  FILE **refv;
  String *refnames;
  int refc;
   
} Session;

extern Session current;

//Will return new session will all variables given default values, an active program allocated, and unused pointers set to NULL
Session newSession(void);

void killSession(Session *toKill);

//should alias to killSession
void endSession(Session *toEnd);

void loadRef(Session *ses, int refn);

void loadRefs(Session *ses);

void newRef(Session *s,FILE *ref, const char* name);

void addProgram(Session *s, String name);

#endif
