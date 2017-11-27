#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// [PRIVATE]

#define CAST _String*self=(_String*)str

typedef struct string
{
  char* chars;

  int length;
  int capacity;
} _String;


// [PUBLIC]

String Str_init_default(void)
{
  return Str_init_maxSize(STR_DEFAULT_MAX_SIZE);
}

String Str_init_maxSize(int maxSize)
{
  _String * self;

  self = (_String*)malloc(sizeof(_String));

  self->chars = (char*)malloc(sizeof(char) * maxSize);
  self->chars[0] = '\0';

  self->capacity = maxSize;

  self->length = 0;

  return self;
} 

String Str_init_const(const char* string)
{
  _String * self;
  int charc,i;

  charc = 0;

  while(string[charc++] != '\0');

  self = Str_init_maxSize((int)((double)(charc * STR_CAPACITY_MODIFIER)));

  for(i = 0; string[i] != '\0' ; i++)
  {
    self->chars[i] = string[i];
  }
  self->length = charc-1;

  return self;
}

void Str_free(String str)
{
  CAST;

  free(self->chars);
  free(self);
}

void Str_edit_append(String str, String add)
{
  CAST;

  printf("TODO: IMPLEMENT Str_edit_append()\n");
}

void Str_edit_insert(String str, String insert, int index)
{
  CAST;

  printf("TODO: IMPLEMENT Str_edit_insert()\n");
}

void Str_edit_overwrite(String str, String insert, int index)
{
  CAST;

  printf("TODO: IMPLEMENT Str_edit_overwrite()\n");
}

void Str_edit_delete(String str)
{
  CAST;

  printf("TODO: IMPLEMENT Str_edit_delete()\n");
}

void Str_edit_deleteRange(String str, int iBegin, int iEnd)
{
  CAST;

  printf("TODO: IMPLEMENT Str_edit_deleteRange()\n");
}

int Str_get_length(String str)
{
  CAST;

  return self->length;
}

char Str_get_char(String str, int index)
{
  CAST;

  if(index < 0 || index >= self->length)
  {
    return '\0';
  }
  else
  {
    return self->chars[index];
  }
}

const char* Str_get_string(String str)
{
  CAST;

  const char* chars;

  chars = (const char*)self->chars;

  return chars;
}

void Str_do_fprint(String str, FILE *fp)
{
  CAST;

  fprintf(fp,"%s",self->chars);
}

void Str_do_print(String str)
{
  Str_do_fprint(str,stdout);
  printf("\n");
}

void Str_do_printDebug(String str)
{
  int i;

  CAST;

  printf("Str(length = %d): ",self->length);
  for(i = 0; i < self->length; i++)
  {
    printf("[%c] ",self->chars[i]);
  }
  printf("END\n");
}
