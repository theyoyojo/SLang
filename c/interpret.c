#include <stdio.h>
#include <string.h>
#include "error.h"
#include "utility.h"
#include "program.h"

#define USE_PROMPT 0
#define USE_FILE 1

bool validateArgc(int argc);

void showHelp(void);

void * handleFlags(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	void *flagActions;
	char ***program;	
	int progLines;
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
		/*
		String test1 = promptForString(20);
		String test2 = promptForString(21);
		String *newLine = (String*)malloc(sizeof(String)*2);
		newLine[0] = test1;
		newLine[1] = test2;
		*/

		StringString line = newStringString(3);
		printf("SS length: %d\n",line.length);
		for(int i = 0; i < line.length; i++)
		{
			//printf("AT i=%d\n",i);
			//printf("SS.strings[%d] length: %d\n",i,line.strings[i].length);
			printf("%s",line.strings[i]);
			/*
			for(int j = 0; j < line.strings[i].length; j++)

			{
				//printf("AT j=%d\n",j);
				printf("%c",line.strings[i].chars[j]);
			}
			*/
			printf(",");
		}
		printf("\n");
		//appendLine(&prog,test1);
		//printf("%d\n",prog.lenLineSymbols[0][1]);
		//printProg(prog);
	}
		
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
	if(argc > 1)
	{
		if(strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
		{
			showHelp();
		}
		else
		{
			printf("Unknown flag \"%s\".\n",argv[1]);
		} 
	}

	return NULL;
}
