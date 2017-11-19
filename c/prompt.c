#include "prompt.h"
#include "utility.h"
#include "program.h"
#include "interpret.h"
#include "parse.h"
#include <stdlib.h>
#include <string.h>

#define PROMPT "SLang>>"
#define PROMPT_DB false

//TODO allow user to adjust buffer with args
#define DEFAULT_BUFFER_SIZE 1000

void systemGenericPrompt(Program *prog)
{
  String raw;
  StringString parsed;
  char clear;
  char* buff;
  int buffLength, i;

  //TEMPORARY
  bool exitCondition;
  exitCondition = false;
    
  
  do
  {
    //prompt the user first
    printf(PROMPT);
    buffLength = getRawLine(stdin,&buff,DEFAULT_BUFFER_SIZE);
    
    //create a new string struct the size of the input buffer (though the allocated memory [raw.capacity] is secretly ~1.3x this amount)
    raw = newString(buffLength);
    PROMPT_DB ? printf("buffLength=%d, begins @%p\n",buffLength,buff) : 0;

    //copy the contents of the buffer to the new string
    for(i = 0; i < buffLength; i++)
    {
      PROMPT_DB ? printf("assigning '%c' to raw.chars[%d] form buff[%d]\n",buff[i],i,i) : 0;
      raw.chars[i] = buff[i];
    }
	
    //free that buffer, we may use it again but we don't want anything in it for the rest of this loop iteration
    PROMPT_DB ? printf("before freedom, buff has this pointer value: %p\n",buff) : 0;
    free(buff); buff = NULL;
    PROMPT_DB ? printf("done, buff is freed, as evidenced by this pointer value: %p \n",buff) : 0;

    //debug info, when flag is toggled this wil display details about the contents of the new string
    if(PROMPT_DB)
    {
      for(i = 0; i < raw.length; i++)
      {
        printf("%d:%c\n",i,raw.chars[i]);
      }
    }

    //temorary exit condition based on first character not being a newline
    clear = raw.chars[0];
    PROMPT_DB ? printf("first char: '%c'\n",clear) : 0;

    PROMPT_DB ? printf("'%s'",raw.chars) : 0;

    //basic exit functionality, this possibly should be changed later for scalability
    if(strcmp(raw.chars,"exit!\n") == 0)
    {
      exitCondition = true;
    }
    else if(strcmp(raw.chars,"help!\n") == 0)
    {
      showHelp();
    }
    else
    {

      //parse the raw string, separate it and validate it, return a StringString and append it to the program
      parsed = parseRawLine(raw);
      PROMPT_DB ? printSS(stdout,parsed) : 0;
      PROMPT_DB ? printf("about to append parsed line @%p\n",&parsed) : 0;
      appendLine(prog,&parsed);
      PROMPT_DB ? printf("DONE appending line\n") : 0;
      
    }

    //now get rid of the raw string, it is no longer needed
    PROMPT_DB ? printf("about to free string raw of length %d, chars located @ %p & String @ %p.\n",raw.length,raw.chars,&raw) : 0;
    killString(&raw);	
    PROMPT_DB ? printf("Success, freed that string as evidenced by this pointer value: %p\n",raw.chars) : 0;

    

  } while (!exitCondition);
  
	
}

void prompt(Program *prog)
{

  if(false) /* here, the progam will detect a user's system and give them an improved prompt if the program is able */
  {
    //TODO
  }
  else
  {
    systemGenericPrompt(prog);
  }
}
