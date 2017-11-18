#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "error.h"
#include "utility.h"
#include "program.h"
#include "prompt.h"

#define USE_PROMPT 0
#define USE_FILE 1

#define MAIN_DB false

bool validateArgc(int argc);

void showHelp(void);

void * handleFlags(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	void *flagActions;
	int interpreterMode;	

	if(!validateArgc(argc))
	{
		showHelp();
		return 1;
	}

	//This is currently the only option until TODO file input is implemented
	interpreterMode = USE_PROMPT;

	flagActions = handleFlags(argc,argv);
	
	if(interpreterMode == USE_PROMPT)
	{
		Program prog = newProgram();
    prompt(&prog);
    MAIN_DB ? printf("MADE IT BACK TO MAIN ALIVE\n") : 0;
		/*
		String test1 = promptForString(20);
		String test2 = promptForString(21);
		String *newLine = (String*)malloc(sizeof(String)*2);
		newLine[0] = test1;
		newLine[1] = test2;
		*/

    /*
    //create test StringStrings
		StringString line1 = newStringString(5);
		StringString line2 = newStringString(5);
		printf("line1 length: %d\n",line1.length);
		printf("line2 length: %d\n",line2.length);
    */

    /*
		for(int i = 0; i < line1.length; i++)
		{
			//printf("AT i=%d\n",i);
			//printf("SS.strings[%d] length: %d\n",i,line.strings[i].length);
			printf("%s",line1.strings[i]);
		
			for(int j = 0; j < line.strings[i].length; j++)

			{
				//printf("AT j=%d\n",j);
				printf("%c",line.strings[i].chars[j]);
			}
			printf(",");
		}
    */

    /*
    //try to append test StringStrings to prog file
		printf("\n");
    //printSS(line1);
    //printSS(line2);
		appendLine(&prog,line1);
		appendLine(&prog,line2);
		//printf("%d\n",prog.lenLineSymbols[0][1]);
		printProg(prog);
    */
    
    /* realloc() driver
    int i;
    int *t = (int*)malloc(sizeof(int)*3);
    for(i = 0; i < 3; i++) { t[i] = i; }

    printf("before realloc(): size=%ld & ",sizeof(t));
    for(i = 0; i < 3; i++)
    {
      printf("[%d] ",t[i]);
    }
    printf("\n");

    t = (int*)safeRealloc(t, sizeof(int) * 4);
    t[3] = 3;

    printf("after realloc(): size=%ld & ",sizeof(t));
    for(i = 0; i < 4; i++)
    {
      printf("[%d] ",t[i]);
    }
    printf("\n");
    */

    printProgram(prog); 
    killProgram(&prog);
	}

	MAIN_DB ? printf("returning 0 after this message.\n") : 0;	
	return 0;
}

bool validateArgc(int argc)
{
	bool isValid = true;
	
	//check for wrong # of args
	switch(argc)
	{
		case 1:
			break;
		case 2:
			break;
		default:
			throwException(TOO_MANY_ARGS); //TODO, evaluate as Exception Struct type, for now will print error
			isValid = false;
			break;
	}
	
	return isValid;
}

void showHelp(void)
{
	printf("Interpreter usage:\nidk lmao\n");
}

void * handleFlags(int argc, char* argv[])
{
  int i;
  for(i = 1; i < argc; i++)
	{
    if(*argv[i] == '-')
    {
      if(strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
      {
        showHelp();
        exit(0);
      }
      else
      {
        printf("Unknown flag \"%s\".\n",argv[1]);
      } 
    }
	}

	return NULL;
}
