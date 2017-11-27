#include "utility.h"
#include "file.h"
#include "os.h"

bool File_get_canRead(const char* filename)
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
  Err_do_string(OS_NOT_IMPLEMENTED,"isReadableFile()");
  return true;
#endif
}

bool File_get_canWrite(const char* filename)
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
  Err_do_string(OS_NOT_IMPLEMENTED,"isWritableFile()");
  return true;
#endif
}

bool File_get_doesExist(const char* filename)
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
  Err_do_string(OS_NOT_IMPLEMENTED,"fileExists()");
  return true;
#endif
}
