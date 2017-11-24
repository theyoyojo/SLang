#include "parse.h"
#include <ctype.h>

//TODO allow user increase of this arbitrary maximum
#define MAX_SYMBOL_BUFFER 1000

#define PARSERAWLINE_DB true

StringString parseRawLine(String raw)
{
  //this is still a stub...............
  //needs design

  //In this branch (9-test-vars-static) I (@theyoyojo) will try to implement basic variable handling
  //For testing and proof-of-concept purposes, I define a valid identifier to be:
  //  --A sequence of alphabetical characters or underscores
  //  --TODO add more to this definition
  //
  //This function will also validate syntax. The calling function should not add the new line to the program if:
  //  --The length of the returned StringString is 0
  //  --The pointer to the array of constituent strings is NULL
  //
  //In this implementation, only global variables will be implemented

  //buffer to store new symbols
  String buff;

  //symbol count to be based to newStringString
  int symc;

  // the array of strings that will become a StringString
  String *parsed;

  //The new StringString to return
  StringString newLine;

  int i;

  bool inIdentifier = false;
  bool inNum = false;
  bool inLiteral = false;
  
  char focus;

  //new symbol buffer
  buff = newString(0);

  PARSERAWLINE_DB ? printf("BEGIN PARSE of %s\n",raw.chars) : 0;

  //new empty StringString for new line
  newLine = newSS(0,NULL);

  for(i = 0; i < raw.length; i++)
  {
    focus = raw.chars[i];
    PARSERAWLINE_DB ? printf("LOOP AT raw[%d] = %c = focus\n",i,focus) : 0;

    //handle quotation marks for literal parsing
    if(focus == '"')
    {
      switch(inLiteral)
      {
        case false: 
          inIdentifier = false;
          inNum = false;
          inLiteral = true;
          appendString(&buff,&focus);
          break;
        case true:
          inLiteral = false;
          appendString(&buff,&focus);
          appendSS(&newLine,&buff);
          buff = newString(0);
          break;
      }
    }
    else if(inLiteral)
    {
      appendString(&buff,&focus);
    }
    else if(isalpha(focus) || focus == '_')
    {
      switch(inIdentifier)
      {
        case false:
          appendSS(&newLine,&buff);
          buff = newString(0);
          inIdentifier = true;
          inNum = false;
          appendString(&buff,&focus);
          break;
        case true:
          appendString(&buff, &focus);
          break;
      }
    }
    else if(isdigit(focus) || (inNum && focus == '.'))
    {
      switch(inNum)
      {
        case false:
          appendSS(&newLine,&buff);
          buff = newString(0);
          inIdentifier = false;
          inNum = true;
          appendString(&buff,&focus);
          break;
        case true:
          appendString(&buff,&focus);
          break;
      }
    }
    else if(focus == '\n')
    {
      inIdentifier = false;
      inNum = false;
      appendSS(&newLine,&buff);
      buff = newString(0);
      appendString(&buff,&focus);
      appendSS(&newLine,&buff);
      break;
    }
    else
    {
      inIdentifier = false;
      inNum = false;
      appendSS(&newLine,&buff);
      buff = newString(0);
      appendString(&buff,&focus);
    }
  }
  
  return newLine;
}
