#include <stdio.h>
#include "string.h"

int main(int argc, int argv[])
{
  String bob;

  bob = Str_init_const("LOREM IPSUM");

  printf("%s\n",Str_get_string(bob));

  printf("[%c] %c\n",Str_get_char(bob,6),Str_get_char(bob,2));

  Str_do_printDebug(bob);

  Str_free(bob);

  return 0;
}

