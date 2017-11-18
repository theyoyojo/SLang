#ifndef PROGRAM_H
#define PROGRAM_H "program.h"
#include "error.h"
#include "utility.h"


typedef struct Program{
	char ***file;
	int lines;
	int *lenLines;
	int **lenLineSymbols;
} Program;

Program newProgram(void);

void killProgram(Program *prog);

void addLine(Program *prog);

void appendLine(Program *prog, StringString newLine);

void printProgram(Program prog);

#endif
