#include "list.h"
#include <stdlib.h>

#define CAST _List*self=(_List*)list

typedef struct list
{
  Object* elements;

  int length;
  int capacity;
} _List;

List List_init_default(void)
{
  _List self;

  self = (_List*)malloc(sizeof(_List));

  self->elements = NULL

  self->length = 0;

  self->capacity = 0;

  return self;
}

void List_free(List list)
{
  free(self->elements);

  free(self);
}

void List_edit_append(List list, Object obj);

void List_edit_insert(List list, Object obj, int index);

void List_edit_delete(List list);

void List_edit_deleteRange(List list, int iBegin, int iEnd);

void List_edit_reverse(List list);

Object List_get_first(List list);

Object List_get_last(List list);

Object List_get_index(List list, int index);

void List_do_print(List list);

