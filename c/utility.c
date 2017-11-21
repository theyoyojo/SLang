#include "utility.h"
#include "interpret.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define SAFEREALLOC_DB false
#define PROMPTFORSTRING_DB true
#define GETRAWLINE_DB false
#define PRINTSS_DB false


String newString(int size)
{
	String new;


  new.capacity = (int)((1.3333)*(double)(size+1));
	new.chars = (char*)malloc(sizeof(char) * new.capacity);
	new.length = size;

	return new;
}

void killString(String *toKill)
{
  free(toKill->chars);
  toKill->chars = NULL;
  toKill->length = 0;
}

void printString(FILE *out, String string)
{
  fprintf(out, "%s\n",string.chars);
}

StringString newStringString(int nStrings, String *strings)
{
	StringString new;
	int i;

  new.capacity = (int)(1.33333*(double)nStrings);
	new.strings = (String*)malloc(sizeof(String) * new.capacity);
	new.length = nStrings;

	for(i = 0; i < nStrings; i++)
	{
		new.strings[i].chars = strings[i].chars;
	}

	return new;
}

String constToString(const char* literal)
{
  String new;
  int lenCount,i;

  lenCount = 0;
  while(literal[lenCount] != '\0') lenCount++;
  lenCount++;

  new = newString(lenCount);
  for(i = 0; i < lenCount; i++) new.chars[i] = literal[i];

  return new;
}
  

void killSS(StringString *murderMe)
{
  int i;
  if(murderMe->strings != NULL)
  {
    for(i = 0; i < murderMe->length; i++)
    {
      killString(&murderMe->strings[i]);
    }
    free(murderMe->strings); murderMe->strings = NULL;
  }
  murderMe->length = 0;
}

String promptForString(int max,const char* prompt)
{
	int i;
	char charin;
	char* buff;
	int buffLength;
	String new;

	buff = (char*)malloc(sizeof(char)*max);
	buffLength = 0;

	printf("%s [%d char limit] >>",prompt,  max);
  scanf(" %c",&charin);
	for(i = 0; i < max; i++)
	{
		buff[i] = charin;
		buffLength++;
    PROMPTFORSTRING_DB ? printf("next: %c @i=%d\n",charin,i) : 0;
		if (isspace(charin) || charin == '\n')
		{
      PROMPTFORSTRING_DB ? printf("found an '\\n'\n") : 0;
			ungetc(charin, stdin);
			buff[i] = '\0';
			break;
			
		}
		scanf("%c",&charin);

	buff[buffLength++] = '\0';
	}

	//clear keyboard buffer
	while(scanf("%c",&charin) == 1 && charin != '\n');

  printf("new string being made of size=%d\n",buffLength);
	new = newString(buffLength);
	new.length = buffLength;

  /*
	for(i = 0; i < max; i++)
	{
		new.chars[i] = '*';
	}
  */


	for(i = 0; i < buffLength; i++)
	{
		new.chars[i] = buff[i];
	}

	return new;
}

void printSS(FILE *out,StringString ss)
{
  int i; 

  for(i = 0; i < ss.length; i++)
  {
    if(PRINTSS_DB)
    {
    fprintf(out,"%c%s%c%c",PRINTSS_DB? '[' : 0,ss.strings[i].chars,PRINTSS_DB? ']' : 0,PRINTSS_DB ? (i < ss.length-1 ? ',' : '\n') : 0);
    }
    else
    {
      fprintf(out,"%s",ss.strings[i].chars);
    }
  }
}

StringString stringCharsToStringString(String str)
{
  int i;
  StringString new;
  String *singleCharStrings; 
  
  singleCharStrings = (String*)malloc(sizeof(String)*str.length);

  for(i = 0; i < str.length; i++)
  {
    singleCharStrings[i] = newString(1);
    singleCharStrings[i].chars[0] = str.chars[i];
    singleCharStrings[i].chars[1] = '\0';
  }

  new = newStringString(str.length, singleCharStrings);

  return new;
}
	
void * safeRealloc(void *ptr, unsigned long int newSize)
{
	void *test;

  SAFEREALLOC_DB ? printf("Starting safeRealloc()\n") : 0;
  SAFEREALLOC_DB ? printf("about to realloc space starting @ %p and make it's size %ld\n",ptr,newSize) : 0;

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
  //memset(*buff,0,sizeof(char) * buffSize);

  for(i = 0; i < buffSize-1; i++)
  {
    gotChar = fscanf(in,"%c",&ch);
    (*buff)[i] = ch;
    buffLength++;
    GETRAWLINE_DB ? printf("loop increment = %d\n",i) : 0;

    if(gotChar == false || ch == '\n')
    {
      //ungetc(ch,in);
      break;
    }
  }
  (*buff)[buffLength++] = '\0';
  
  /* test print buff
  for(i = 0; i < buffLength; i++)
  {
    printf("%c",(*buff)[i]);
  }
  */
  return buffLength;
  
}
bool getUserBool(const char* prompt)
{
  char c,clear;

  printf("%s [y/n]>",prompt);
  while(scanf("%c", &c) != 1 || !(c == 'y' || c == 'Y' || c == 'n' || c == 'N'))
  {
    ungetc(c,stdin);
    while(scanf("%c",&clear) == 1 && clear != '\n');
    printf("That is an invalid choice.\n%s [y/n]>",prompt);
  }
  while(scanf("%c",&clear) == 1 && clear != '\n');

  switch(c)
  {
    case 'y':
    case 'Y':
      return true;
      break;
    case 'n':
    case 'N':
      return false;
      break;
    default:
      fprintf(stderr, "Implementation error in getUserBool().\n");
      break;
  }

}

bool isReadableFile(const char* filename)
{
  if(access(filename,R_OK) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool isWritableFile(const char* filename)
{
  if(access(filename,W_OK) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
