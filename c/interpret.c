#include <string.h>
#include "error.h"
#include "utility.h"
#include "program.h"
#include "prompt.h"
#include "interpret.h"
#include <ctype.h>

#define MAIN_DB false
#define HANDLEARGS_DB false

bool validateArgc(int argc);

void showHelp(void);

void  handleArgs(int argc, char* argv[]);

Session current;

int main(int argc, char* argv[])
{
  bool willSaveBuffer;

	if(!validateArgc(argc))
	{
		showHelp();
		return 1;
	}

  current = newSession();

	handleArgs(argc,argv);
  
  //printString(stdout,promptForString(100,"entersometing"));

  MAIN_DB ? printf("REFC: %d\n",current.refc) : 0;
  if(current.refc > 0)
  {
    loadRefs(&current);
  }

  MAIN_DB ? printf("[!]after files are handled, this is current.active.lines: %p\n",current.active->lines) : 0;
	
	if(current.mode == INTERACTIVE)
	{
    //printf("current.active is @ %p, current.filev is @ %p\n",current.active,current.filev);
    prompt(&current.filev[0]); //I wanted to use current.active, but loadRefs changes the pointer. Why?

    //printf("%d\n",isspace('\n'));

    if(getUserBool("Would you like to save the live buffer?"))
    {
      saveProgram(current.filev[0]);
    }
          
    MAIN_DB ? printf("MADE IT BACK TO MAIN ALIVE\n") : 0;

	}

  MAIN_DB ? printf("filec=%d\n",current.filec) :0;
  
  //this is temporary for testing purposes
  for(int i = 0; i < current.filec; i++)
  {
    printf("===[PROGRAM '%s']===:\n",current.filev[i].name.chars);
    printProgram(stdout, current.filev[i]);
  }
        

  MAIN_DB ? printf("haven't crashed\n") : 0;
  endSession(&current);

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
		case 2:
    case 3:
    case 4:
    case 5:
    case 6:
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
	printf("Interpreter argument usage:\n");
  printf("-h || --help : Show this message\n");
  printf("-i || --interactive : force enable interractive prompt\n");
  printf("<filename> : attempt to load a file with name \"filename\"\n");
  printf("NOTE: Loading a file will disable shell unless otherwise specified\n");
}

void handleArgs(int argc, char* argv[])
{
  int i;
  FILE **argrefv;
  int argrefc;
  bool userWantsPrompt;

  userWantsPrompt = false;

  argrefv = (FILE**)malloc(sizeof(FILE*)*argc);
  argrefc = 0;

  for(i = 1; i < argc; i++)
	{
    if(*argv[i] == '-')
    {
      if(strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
      {
        showHelp();
        free(argrefv);
        exit(0);
      }
      else if(strcmp(argv[1],"-i") == 0 || strcmp(argv[1],"--interactive") == 0)
      {
        current.mode = INTERACTIVE;   
        userWantsPrompt = true;
      }
      else
      {
        printf("Unknown flag \"%s\".\n",argv[1]);
      } 
    }
    else
    {
      //if the arg is not preceeded by an '-' we attempt to open it as a file
      argrefv[argrefc] = fopen(argv[i],"r");
      if (argrefv[argrefc] == NULL)
      {
        throwExceptionWithString(FILE_NOT_FOUND,argv[i]);
        //fprintf(stderr,"Could not find a file by the name of '%s'.\n",argv[i]);
      }
      else
      {
        //TODO check for that file already being opened, because it works for now, but perhaps it shouldn't 
        //current.refv = (FILE**)safeRealloc(current.refv,sizeof(FILE*) * ++current.refc);
        //current.refv[current.refc-1] = argrefv[argrefc]; 

        newRef(&current,argrefv[argrefc],argv[i]);
      }

      //Unless the -i flag is specified, the prompt not be displayed if a file open attempt is made, regardless of its success
      if(!userWantsPrompt)
      {
        current.mode = SCRIPT;
      }
      argrefc++;

    }
	}

  free(argrefv);
}
