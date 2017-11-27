#include "utility.h"
#include "error.h"

void * Util_get_safeRealloc(void * ptr, unsigned long int size)
{
  void * test;

  test = realloc(ptr,size);
  if(test == NULL)
  {
    Err_do_default(REALLOC_FAIL);
  }
  return test;
}
