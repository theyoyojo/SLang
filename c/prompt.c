#include "prompt.h"
#include "utility.h"
#include "program.h"
#include <stdlib.h>

#define PROMPT "SLang>>"
#define PROMPT_DB false

//TODO allow user to adjust buffer with args
#define DEFAULT_BUFFER_SIZE 1000

void prompt(Program *prog)
{
  String raw;
  StringString decomposed;
  char clear;
  char* buff;
  int buffLength, i;

  //TEMPORARY
  int exitCondition;
  exitCondition = true;
    
  
  do
  {
    printf(PROMPT);
    buffLength = getRawLine(stdin,&buff,DEFAULT_BUFFER_SIZE);
    
    raw = newString(buffLength);
    PROMPT_DB ? printf("buffLength=%d, begins @%p\n",buffLength,buff) : 0;

    for(i = 0; i < buffLength; i++)
    {
      PROMPT_DB ? printf("assigning '%c' to raw.chars[%d] form buff[%d]\n",buff[i],i,i) : 0;
      raw.chars[i] = buff[i];
    }
	
    PROMPT_DB ? printf("before freedom, buff has this pointer value: %p\n",buff) : 0;
    free(buff); buff = NULL;
    PROMPT_DB ? printf("done, buff is freed, as evidenced by this pointer value: %p \n",buff) : 0;

    if(PROMPT_DB)
    {
      for(i = 0; i < raw.length; i++)
      {
        printf("%d:%c\n",i,raw.chars[i]);
      }
    }

    clear = raw.chars[0];
    PROMPT_DB ? printf("first char: '%c'\n",clear) : 0;

    printf("%s",raw.chars);


    decomposed = stringCharsToStringString(raw);
    printSS(decomposed);
    appendLine(prog,decomposed);

    PROMPT_DB ? printf("about to free string raw of length %d, chars located @ %p & String @ %p.\n",raw.length,raw.chars,&raw) : 0;
    killString(&raw);	
    PROMPT_DB ? printf("Success, freed that string as evidenced by this pointer value: %p\n",raw.chars) : 0;

    

  } while (clear != '\n');
  
	
}
