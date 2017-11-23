#include <string.h>
#include "error.h"
#include "utility.h"
#include "program.h"
#include "prompt.h"
#include "interpret.h"
#include "os.h"
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

  MAIN_DB ? printf("You are using a %s machine.\n",OS_NAME) : 0;

  current = newSession();

	handleArgs(argc,argv);
  

  MAIN_DB ? printf("REFC: %d\n",current.refc) : 0;
  if(current.refc > 0)
  {
    loadRefs(&current);
  }

  MAIN_DB ? printf("[!]after files are handled, this is current.active.lines: %p\n",current.active->lines) : 0;
	
	if(current.mode == INTERACTIVE)
	{
    prompt(current.active); 

    if(getUserBool("Would you like to save the live buffer?"))
    {
      saveProgram(*current.active);
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
      argrefv[argrefc] = fopen(argv[i],"r");
      //throw permissions error if file exists but read permissions are denied
      if(fileExists(argv[i]) && !isReadableFile(argv[i]))
      {
        throwExceptionWithString(FILE_READ_ACCESS_DENIED,argv[i]);
      }
      //if the arg is not preceeded by an '-' we attempt to open it as a file
      else if (argrefv[argrefc] == NULL)
      {
        throwExceptionWithString(FILE_NOT_FOUND,argv[i]);
        //fprintf(stderr,"Could not find a file by the name of '%s'.\n",argv[i]);
      }
      else
      {
        //TODO check for that file already being opened, because it works for now, but perhaps it shouldn't 

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
