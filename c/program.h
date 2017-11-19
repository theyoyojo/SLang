#ifndef PROGRAM_H
#define PROGRAM_H "program.h"
#include "error.h"
#include "utility.h"
#include <stdio.h>

/*
typedef struct Program{
	char ***file;
	int lines;
	int *lenLines;
	int **lenLineSymbols;
} Program;

*/

typedef struct Program
{
  StringString *lines;
  String name;
  int length;
  int capacity;

} Program;

Program newProgram(String name);

void killProgram(Program *prog);

void addLine(Program *prog);

void appendLine(Program *prog, StringString *newLine);

void printProgram(FILE *out, Program prog);

void saveProgram(Program prog);

#endif
