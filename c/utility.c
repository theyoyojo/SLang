#include "utility.h"
#include "interpret.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "os.h"

#define SAFEREALLOC_DB false
#define PROMPTFORSTRING_DB false
#define GETRAWLINE_DB false
#define PRINTSTRING_DB false
#define PRINTSS_DB false
#define APPENDSTRING_DB true
#define INSERTSTRING_DB false
#define INSERTSS_DB false


String newString(int size)
{
	String new;


  if(size > 0)
  {
    new.capacity = (int)((1.3333)*(double)(size+1));
    new.chars = (char*)malloc(sizeof(char) * new.capacity);
    new.length = size;
  }
  else
  {
    new.capacity = 0;
    new.chars = NULL;
    new.length = 0;
  }

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
  if(PRINTSTRING_DB)
  {
    for(int i = 0; i < string.length; i++)
    {
      fprintf(out,"[%c]",string.chars[i]);
    }
    fprintf(out,"\n");
  }
  else
  {
    fprintf(out, "%s\n",string.chars);
  }
}

void appendString(String *s, const char* add)
{
  int i;

  APPENDSTRING_DB ? printf("appending string %s to String:",add) : 0;
  APPENDSTRING_DB ? printString(stdout, *s) : 0;

  for(i = 0; add[i] != '\0'; i++)
  {
    //the "-1" is in order to overwrite the null terminator, added back in later
    //if there is space for another character in the string, add it
    APPENDSTRING_DB ? printf("before append: capacity: %d, length %d\n",s->capacity,s->length) : 0;
    if(s->capacity > s->length)
    {
      s->chars[s->length-1] = add[i];
      s->length++;
    }
    //if there isn't enough space, more will need to be allocated
    else if(s->capacity == 0)
    {
      //arbitrary choice of 10 but reasonable, will be realloc'd as needed anyway  
      s->capacity = 10;
      s->chars = (char*)malloc(sizeof(char) * s->capacity+1);
      s->chars[0] = add[i];
      s->chars[1] = '\0';
      s->length = 2;
    }
    else
    {
      APPENDSTRING_DB ? printf("@add[%d] = %c, allocating more space\n",i,add[i]) : 0;
      s->capacity = (int)((1.3333) * (double)(s->capacity+1));
      APPENDSTRING_DB ? printf("new capacity: %d\n",s->capacity) : 0;
      s->chars = (char*)safeRealloc(s->chars,sizeof(char) * (unsigned long int)s->capacity);
      APPENDSTRING_DB ? printf("done realloc, overwriting s[%d]=%c with %c\n",s->length -1,s->chars[s->length-1 + i],add[i]) : 0;
      s->chars[s->length-1] = add[i];
      s->length++;
    }
  }
  //add the null terminator back onto the end if it isn't already there
  APPENDSTRING_DB ? printf("[%c] @%d\n",s->chars[s->length-1],s->length-1) : 0;
  if(s->chars[s->length-1] != '\0')
  {
    APPENDSTRING_DB ? printf("null not detected\n") : 0;
    s->chars[s->length-1] = '\0';
    s->length++;
  }
}
  
void insertString(String *s, const char* insert, int index)
{
  int i,j;

  //default to append if index is invalid
  index = index > s->length - 1 || index < 0 ? s->length-1 : index;
  index = index < 0 ? 0 : index;
  
  INSERTSTRING_DB ? printf("insert index: %d\n to string @%p\n",index,s) : 0;

  for(i = 0; insert[i] != '\0'; i++)
  {
    if (INSERTSTRING_DB)
    {
      printf("i=%d, string=\n",i);
      printString(stdout,*s);
    }
    //same check as appendString()
    if(s->capacity > s->length)
    {
      for(j = s->length; j >= index + i; j--)
      {
        INSERTSTRING_DB ? printf("move char %c @chars[%d] to chars[%d]\n",s->chars[j],j,j+1) : 0;
        s->chars[j+1] = s->chars[j];
        INSERTSTRING_DB ? printf("new chars[%d] is %c\n",j+1,s->chars[j+1]) : 0;
      }
      s->chars[index + i] = insert[i];
      s->length++;
    }
    else if(s->capacity == 0)
    {
      appendString(s,insert);
      INSERTSTRING_DB ? printf("new length: %d\n",s->length) : 0;
      return;
    }
    else
    {
      INSERTSTRING_DB ?  printf("realloc @i=%d\n",i) : 0;
      s->capacity = (int)((1.3333) * (double)(s->capacity+1));
      INSERTSTRING_DB ? printf("new capacity xx = %d\n",s->capacity) : 0;
      s->chars = (char*)safeRealloc(s->chars,sizeof(char) * (unsigned long int)s->capacity);
      for(j = s->length; j >= index + i; j--)
      {
        s->chars[j+1] = s->chars[j];
      }
      s->chars[index + i] = insert[i];
      s->length++;
    }

  } 
}


StringString newStringString(int nStrings, String *strings)
{
	StringString new;
	int i;

  if(nStrings > 0)
  {
    new.capacity = (int)(1.33333*(double)nStrings);
    new.strings = (String*)malloc(sizeof(String) * new.capacity);
    new.length = nStrings;

    for(i = 0; i < nStrings; i++)
    {
      new.strings[i].chars = strings[i].chars;
    }
  }
  else
  {
    new.capacity = 0;
    new.strings = NULL;
    new.length = 0;
  }

	return new;
}

StringString newSS(int nStrings, String *strings)
{
  newStringString(nStrings,strings);
}

void appendStringString(StringString *ss, String *s)
{
  if(ss->capacity > ss->length)
  {
    ss->strings[ss->length++] = *s;
  }
  else if(ss->capacity == 0)
  {
    //10 is an arbitrarily chosen defauly capacity to add to an empty StringString
    //I don't think this number particularly matters because the capacity is dynamically realloc'd as needed
    ss->capacity = 10;
    ss->strings = (String*)malloc(sizeof(String) * 10);
    ss->strings[0] = *s;
    ss->length = 1;
  }
  else
  {
    ss->capacity = (int)((1.3333) * (double)(ss->capacity));
    ss->strings = (String*)safeRealloc(ss->strings,sizeof(String) * ss->capacity);
    ss->strings[ss->length++] = *s;
  }
}

void appendSS(StringString *ss, String *s)
{
  appendStringString(ss,s);
}

void insertStringString(StringString *ss, String *s, int index)
{
  int i;
  //if the index at which to insert is past the end of the array, insert at the end of the array instead
  //default to append if index is invalid
  index = index > ss->length || index < 0 ? ss->length : index; 

  INSERTSS_DB ? printf("begining: index=%d, length=%d, capacity=%d\n",index,ss->length,ss->capacity) : 0;
  //if the capacity of *ss is greater than its length, just insert and don't realloc
  if(ss->capacity > ss->length)
  {
    INSERTSS_DB ? printf("in regular loop\n") : 0;
    for(i = ss->length-1; i >= index; i--)
    {
      if(INSERTSS_DB)
      {
        printf("moving string @i:");
        printString(stdout,ss->strings[i]);
        printf("to index %d\n",i+1);
      }
      ss->strings[i+1] = ss->strings[i];
    }
    ss->strings[index] = *s;
    ss->length++;
  }
  else if(ss->capacity == 0)
  {
    INSERTSS_DB ? printf("about to call appendSS()\n") : 0;
    appendStringString(ss,s);
  }
  else
  {
    INSERTSS_DB ? printf("about to realloc") : 0;
    ss->capacity = (int)((1.3333) * (double)(ss->capacity));
    ss->strings = (String*)safeRealloc(ss->strings,sizeof(String) * ss->capacity);
    for(i = ss->length-1; i >= index; i--)
    {
      ss->strings[i+1] = ss->strings[i];
    }
    ss->strings[index] = *s;
    ss->length++;
  }

}

void insertSS(StringString *ss, String *s, int index)
{
  insertStringString(ss,s,index);
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

void killStringString(StringString *murderMe)
{
  killSS(murderMe);
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

  PROMPTFORSTRING_DB ? printf("new string being made of size=%d\n",buffLength) : 0;
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

void printStringString(FILE *out, StringString ss)
{
  printSS(out,ss);
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
#if OS == OS_LINUX
  if(access(filename,R_OK) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
#else
  throwExceptionWithString(OS_NOT_IMPLEMENTED,"isReadableFile()");
  return true;
#endif
}

bool isWritableFile(const char* filename)
{
#if OS == OS_LINUX
  if(access(filename,W_OK) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
#else
  throwExceptionWithString(OS_NOT_IMPLEMENTED,"isWritableFile()");
  return true;
#endif
}



bool fileExists(const char* filename)
{
#if OS == OS_LINUX
  if(access(filename,F_OK) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
#else
  throwExceptionWithString(OS_NOT_IMPLEMENTED,"fileExists()");
  return true;
#endif
}
