#include <stdlib.h>
#include <stdio.h>
#include "program.h"
#include "utility.h"
#include "interpret.h"
#include "unistd.h"
#include "error.h"

#define APPENDLINE_DB false
#define ADDLINE_DB false
#define PRINTPROG_DB false
#define KILL_DB false


Program newProgram(String name)
{
  Program new;

  new.name = name;

  new.lines = NULL;
  new.length = 0;
  new.capacity = 0;

  return new;
}

void killProgram(Program *prog)
{
  int i;
  KILL_DB ? printf("killing program\n") : 0;
  if(prog->lines != NULL)
  {
    for(i = 0; i < prog->length; i++)
    {
      killSS(&prog->lines[i]);
    }
    free(prog->lines); prog->lines = NULL;
  }
  prog->length = 0;

  //program is kill

  KILL_DB ? printf("program is kill\n") : 0;
}


void addLine(Program *prog)
{
  prog->length++;
  ADDLINE_DB ? printf("adding line to prog->lines @ %p: new length of prog is:%d\n",prog->lines, prog->length) : 0;

  /*
  if(prog->lines == NULL)
  {
    prog->lines = (StringString*)malloc(sizeof(StringString) * prog->length);
  }
  else
  {
  */
  prog->lines = (StringString*)safeRealloc(prog->lines,sizeof(StringString) * prog->length);
  //}
  ADDLINE_DB ? printf("successfully added line\n") : 0;
}

void appendLine(Program *prog, StringString *line)
{
  addLine(prog);
  APPENDLINE_DB ? printf("added line to prog\n") : 0;

  prog->lines[prog->length-1] = *line;
  
  if(APPENDLINE_DB)
  {
    printf("appending line from %p. line follows:\n",line);
    printSS(stdout, *line);
    printf("END OF LINE\n");
  }

  //killSS(&line);
}

void printProgram(FILE *out,Program prog)
{
  int i;

  PRINTPROG_DB ? fprintf(stdout,"printing program of length %d.\n",prog.length) : 0;
  for(i = 0; i < prog.length; i++)
  {
    printSS(out,prog.lines[i]);
  }
}

void saveProgram(Program prog)
{
  FILE *new;
  String name;

  name = promptForString(DEFAULT_BUFFER_SIZE,"Enter a name for this file ");
  printString(stdout,name);
  
  if(access(name.chars,F_OK) == -1)
  {
    new = fopen(name.chars,"w");
  }
  else 
  {
    if(getUserBool("A file by that name already exists, overwrite?"))
    {
      if(!isWritableFile(name.chars))
      {
        throwExceptionWithString(FILE_WRITE_ACCESS_DENIED,name.chars);
      }
      else
      {
        new = fopen(name.chars, "w");
      }
    }
    else if(getUserBool("Would you like to try another name? If you choose no, the buffer will be lost."))
    {
      saveProgram(prog);
      return;
    }
    else
    {
      return;
    }
  }


  printProgram(new,prog); 
  fclose(new);
  

}

/* the old way of doing thngs is below. This involves dynamically allocating and reallocating a char*** for some reason,
 * getting rid of StringStrings, and keeping track of lengths seperately. As you can expect, it caused many an unforseen segfault.

Program newProgram(void)
{
	Program prog;
	prog.lines = 0;
	prog.lenLines = NULL;
	prog.lenLineSymbols = NULL;
	prog.file = NULL;
	
	return prog;
}

void killProgram(Program *prog)
{
  //i = the line in the file
  //j = the symbol (char array) in line i
  //k = the char in symbol j on line i
  int i,j,k;

  if(prog->file != NULL)
  {
    for(i = 0; i < prog->lines; i++)
    {
      if(prog->file[i] != NULL)
      {
        for(j = 0; j < prog->lenLines[i]; j++)
        {
          if(prog->file[i][j] != NULL)
          {
            free(prog->file[i][j]); prog->file[i][j] = NULL;
          }
        }
      free(prog->lenLineSymbols[i]); prog->lenLineSymbols[i] = NULL;
      free(prog->file[i]); prog->file[i] = NULL;
      }
    }
    free(prog->lenLineSymbols); prog->lenLineSymbols = NULL;
    free(prog->lenLines); prog->lenLines = NULL;
    free(prog->file); prog->file = NULL;
    //program is kill     
  }
}


void addLine(Program *prog)
{
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

void printProgram(Program prog) { int i,j,k;

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

*/
