#include <stdlib.h>
#include <stdio.h>
#include "program.h"

#define APPENDLINE_DB 0
#define ADDLINE_DB 0
#define PRINTPROG_DB 0

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
    prog->lenLineSymbols = (int**)malloc(sizeof(int*) * prog->lines);
	}
	else
	{
    ADDLINE_DB ? printf("about to realloc the file and associated length vectors\n") : 0;
		prog->file = (char***)safeRealloc(prog->file,sizeof(char(**)) * prog->lines); //#1
    ADDLINE_DB ? printf("done with #%d\n",1) : 0;
		prog->lenLines = (int*)safeRealloc(prog->lenLines,sizeof(int) * prog->lines); //#2
    ADDLINE_DB ? printf("done with #%d\n",2) : 0;
    prog->lenLineSymbols = (int**)safeRealloc(prog->lenLineSymbols,sizeof(int*) * prog->lines); //#3
    ADDLINE_DB ? printf("done with #%d\n",3) : 0;
	}
}

void appendLine(Program *prog, StringString newLine)
{
	int i,j;

  APPENDLINE_DB ? printf("gonna allocate a new line\n") : 0;
	addLine(prog);
  APPENDLINE_DB ? printf("BOUTTA DO FILE MALLOC bro\n") : 0;
	prog->file[prog->lines-1] = (char**)malloc(sizeof(char*)*newLine.length);
  APPENDLINE_DB ? printf("just malloc'd %ld bytes to file at line %d to address %p\n",sizeof(char**)*newLine.length,prog->lines,prog->file[prog->lines-1]) : 0;

	APPENDLINE_DB ? printf("# of strings in newLine = %d\n",newLine.length) : 0;
	prog->lenLines[prog->lines-1] = newLine.length;

	prog->lenLineSymbols[prog->lines-1] = (int*)malloc(sizeof(int)*newLine.length);

	APPENDLINE_DB ? printf("prog->lines-1 = %d\n",prog->lines-1) : 0;

	for(i = 0; i < newLine.length; i++)
	{
    if(APPENDLINE_DB)
    {
      printf("APPEND LINE LOOP i=%d\n",i);
      printf("i=%d and newLine.length =%d\n",i,newLine.length);
      printf("about to assisgn %ld bytes to pointer %p @line %d symbol %d\n",sizeof(char) * newLine.strings[i].length,prog->file[prog->lines-1][i],prog->lines, i);
    }

		prog->file[prog->lines-1][i] = (char*)malloc(sizeof(char) * newLine.strings[i].length);

    if(APPENDLINE_DB)
    {
      printf("new pointer is now %p\n",prog->file[prog->lines-1][i]);
      printf("just allocated memory for line %d string %d\n",prog->lines,i);
    }

    for(j = 0; j < newLine.strings[i].length; j++)
    {
      prog->file[prog->lines-1][i][j] = newLine.strings[i].chars[j];
    }
		APPENDLINE_DB ? printf("lenLineSymbols @ [%d][%d] assignment follows\n",prog->lines-1,i) : 0;
		prog->lenLineSymbols[prog->lines-1][i] = newLine.strings[i].length;
		APPENDLINE_DB ? printf("assignment made, value is now: %d\n",prog->lenLineSymbols[prog->lines-1][i]) : 0;
	}
}

void printProg(Program prog) { int i,j,k;

	PRINTPROG_DB ? printf("BEGIN PRINT PROG ()\n") : 0;

	for(i = 0; i < prog.lines; i++)
	{
		PRINTPROG_DB ? printf("[") : 0;
		for(j = 0; j < prog.lenLines[i]; j++)
		{
			PRINTPROG_DB ? printf("'") : 0;
			for(k = 0; k < prog.lenLineSymbols[i][j]; k++)
			{
				printf("%c",prog.file[i][j][k]);
			}
			PRINTPROG_DB ? printf("', ") : 0;
		}
		PRINTPROG_DB ? printf("]\n") : 0;
	}
	printf("\n");
}
