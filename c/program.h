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

void addLine(Program *prog);

void appendLine(Program *prog, String newLine);

void printProg(Program prog);

#endif
