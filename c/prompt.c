#include "prompt.h"
#include "utility.h"
#include "program.h"
#include "parse.h"
#include <stdlib.h>

#define PROMPT "SLang>>"
#define PROMPT_DB true

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
  int exitCondition;
  exitCondition = true;
    
  
  do
  {
    //prompt the user first
    printf(PROMPT);
    buffLength = getRawLine(stdin,&buff,DEFAULT_BUFFER_SIZE);
    
    //create a new string struct the size of the input buffer (though the allocated memory [raw.capacity] is secretly ~1.3x this amount)
    printf("I m about to make that new string brother and sister it iwll be %d chars long\n",buffLength);
    raw = newString(buffLength);
    printf("IM IN THA PROMPT JUT AFTER making nu strin n shiet\n");
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

    PROMPT_DB ? printf("%s",raw.chars) : 0;


    //parse the raw string, separate it and validate it, return a StringString and append it to the program
    parsed = parseRawLine(raw);
    PROMPT_DB ? printSS(parsed) : 0;
    appendLine(prog,&parsed);


    //now get rid of the raw string, it is no longer needed
    PROMPT_DB ? printf("about to free string raw of length %d, chars located @ %p & String @ %p.\n",raw.length,raw.chars,&raw) : 0;
    killString(&raw);	
    PROMPT_DB ? printf("Success, freed that string as evidenced by this pointer value: %p\n",raw.chars) : 0;

    

  } while (clear != '\n');
  
	
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
