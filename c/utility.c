#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFEREALLOC_DB false
#define PROMPTFORSTRING_DB false
#define GETRAWLINE_DB false

String newString(int size)
{
	String new;

  new.capacity = (int)((1.3333)*(double)(size+1));
	new.chars = (char*)malloc(sizeof(char) * new.capacity);
	new.length = size+1;

	return new;
}

StringString newStringString(int nStrings, String *strings)
{
	StringString new;
	int i;

	new.strings = (String*)malloc(sizeof(String) * nStrings);
	new.length = nStrings;

	for(i = 0; i < nStrings; i++)
	{
		new.strings[i].chars = strings[i].chars;
	}

	return new;
}

String promptForString(int max)
{
	int i;
	char charin;
	char* buff;
	int buffLength;
	String new;

	buff = (char*)malloc(sizeof(char)*max);
	buffLength = 0;

	printf("Enter a string, max size is %d >>",max);
	for(i = 0; i < max; i++)
	{
		scanf("%c",&charin);
		buff[i] = charin;
		buffLength++;
    PROMPTFORSTRING_DB ? printf("next: %c @i=%d\n",charin,i) : 0;
		if (charin == '\n')
		{
      PROMPTFORSTRING_DB ? printf("found an '\\n'\n") : 0;
			ungetc(charin, stdin);
			//buff[buffLength++] = '\0';
			break;
			
		}

	}
	buff[buffLength++] = '\0';

	//clear keyboard buffer
	while(scanf("%c",&charin) == 1 && charin != '\n');

	new = newString(buffLength);
	new.length = buffLength;

	for(i = 0; i < max; i++)
	{
		new.chars[i] = '*';
	}


	for(i = 0; i < buffLength; i++)
	{
		new.chars[i] = buff[i];
	}

	return new;
}

void printSS(StringString ss)
{
  int i; 

  for(i = 0; i < ss.length; i++)
  {
    printf("[%s]%c",ss.strings[i].chars,i < ss.length-1 ? ',' : '\n');
  }
}

StringString stringCharsToStringString(String str)
{
  int i;
  StringString new;
  String *singleCharStrings; 

  for(i = 0; i < str.length; i++)
  {
    singleCharStrings[i] = newString(1);
    singleCharStrings[i].chars[0] = str.chars[i];
    singleCharStrings[i].chars[1] = '\0';
  }

  new = newStringString(str.length, singleCharStrings);

  return new;
}
	
void * safeRealloc(void *ptr, int newSize)
{
	void *test;

  SAFEREALLOC_DB ? printf("Starting safeRealloc()\n") : 0;

	test = realloc(ptr,newSize);
  SAFEREALLOC_DB ? printf("made testPointer\n") : 0;
	if(test == NULL)
	{
		throwException(REALLOC_FAIL);
	}
  return test;
}

int getRawLine(FILE *in, char** buff, int buffSize)
{
  int buffLength,i;
  char ch;
  bool gotChar;

  buffLength = 0;
  *buff = (char*)malloc(sizeof(char) * buffSize);
  memset(*buff,0,sizeof(char) * buffSize);

  for(i = 0; i < buffSize-1; i++)
  {
    gotChar = fscanf(in,"%c",&ch);
    (*buff)[i] = ch;
    buffLength++;
    GETRAWLINE_DB ? printf("loop increment = %d\n",i) : 0;

    if(gotChar == false || ch == '\n')
    {
      break;
    }
  }
  buff[++buffLength] = '\0';
  
  /* test print buff
  for(i = 0; i < buffLength; i++)
  {
    printf("%c",(*buff)[i]);
  }
  */
  return buffLength;
  
}
