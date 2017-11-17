#include "prompt.h"
#include "utility.h"
#include "program.h"
#include <stdlib.h>

//TODO allow user to adjust buffer with args
#define RAW_INPUT_BUFFER_SIZE 1000

void prompt(Program *prog)
{
  String raw;
  char clear;
  char* buff;
  int buffLength, i;

  //TEMPORARY
  int exitCondition;
  exitCondition = true;
    
  do
  {
    buff = NULL;
    printf("SLang>>");
    buffLength = getRawLine(stdin,&buff,RAW_INPUT_BUFFER_SIZE);

    raw = newString(buffLength);
    printf("buffLength=%d\n",buffLength);
    for(i = 0; i < buffLength; i++)
    {
      raw.chars[i] = buff[i];
    }

          
    printf("%s",buff);
    printf("done\n");

  } while (buff[0] != '\n');
}
	

