#include <stdlib.h>
#include <stdio.h>
#include "program.h"

Program newProgram(void)
{
	Program prog;
	prog.lines = 0;
	prog.lenLines = NULL;
	prog.lenLineSymbols = NULL;
	prog.file = NULL;
	
	return prog;
}


void addLine(Program *prog)
{
	char ***ptrFileTest;

	prog->lines++;

	if(prog->file == NULL)
	{
		prog->file = (char***)malloc(sizeof(char**) * prog->lines);
		prog->lenLines = (int*)malloc(sizeof(int) * prog->lines);
	}
	else
	{
		safeRealloc(&prog->file,sizeof(char(**)) * prog->lines);
		safeRealloc(&prog->lenLines,sizeof(int) * prog->lines);
	}
}

//Should eventually take a char** instead of String TODO
void appendLine(Program *prog, String newLine)
{
	int i;

	addLine(prog);
	prog->file[prog->lines-1] = (char**)malloc(sizeof(char*)*newLine.length);

	printf("len of newLine = %d\n",newLine.length);
	prog->lenLines[prog->lines-1] = newLine.length;

	prog->lenLineSymbols = (int**)malloc(sizeof(int*) * prog->lenLines[prog->lines-1]);
	prog->lenLineSymbols[prog->lines-1] = (int*)malloc(sizeof(int)*newLine.length);

	printf("prog->lines-1 = %d\n",prog->lines-1);

	for(i = 0; i < newLine.length; i++)
	{
		prog->file[prog->lines-1][i] = (char*)malloc(sizeof(char));
		prog->file[prog->lines-1][i][0] = newLine.chars[i];
		printf("lenLineSymbols @ [%d][%d] assignment follows\n",prog->lines-1,i);
		prog->lenLineSymbols[prog->lines-1][i] = 1;
		printf("assignment made, value is now: %d\n",prog->lenLineSymbols[prog->lines-1][i]);
	}
}

void printProg(Program prog)
{
	int i,j,k;

	printf("BEGIN PRINT PROG ()\n");

	for(i = 0; i < prog.lines; i++)
	{
		printf("[");
		//printf("i incremented to %d.\n",i);
		for(j = 0; j < prog.lenLines[i]; j++)
		{
			printf("'");
			//printf("j incremented to %d.\n",j);
			for(k = 0; k < prog.lenLineSymbols[i][j]; k++)
			{
				//printf("k incremented to %d.\n",k);
				printf("%c",prog.file[i][j][k]);
			}
			printf("', ");
		}
		printf("]");
	}
	printf("\n");
}
