#include <stdio.h>
#include "error.h"

void throwException(int error)
{
	switch(error)
	{
		case TOO_MANY_ARGS:
			fprintf(stderr,"[ERROR] Too many args.\n");
			break;
		case REALLOC_FAIL:
			fprintf(stderr,"[ERROR] Unable to reallocate memory. Check your available RAM.\n");
			break;
    case FILE_NOT_FOUND:
      fprintf(stderr,"[ERROR] A file was not found. This error has been raised without a specified filename\n");
      break;
    case BAD_FILE_READ:
      fprintf(stderr,"[ERROR] Something went wrong while reading an unspecified file.\n");
      break;
    case FILE_READ_ACCESS_DENIED:
      fprintf(stderr,"[ERROR] Read access denied for unspecified file.\n");
      break;
    case FILE_WRITE_ACCESS_DENIED:
      fprintf(stderr,"[ERROR] Write access denied for unspecified file.\n");
      break;
		default:
			fprintf(stderr,"[ERROR] An unknown error occured.\n");
			break;
	}
}

//If an error has a value that needs to be printed, this should be called instead
//The exception should be raised no matter which function is called however
void throwExceptionWithString(int error, const char* string)
{
  switch(error)
	{
		case TOO_MANY_ARGS:
			fprintf(stderr,"[ERROR] Too many args.\n");
			break;
		case REALLOC_FAIL:
			fprintf(stderr,"[ERROR] Unable to reallocate memory. Check your available RAM.\n");
			break;
    case FILE_NOT_FOUND:
      fprintf(stderr,"[ERROR] Could not find a file by the name of '%s'.\n",string);
      break;
    case BAD_FILE_READ:
      fprintf(stderr,"[ERROR] Something went wrong while reading from file '%s'.\n",string);
      break;
    case FILE_READ_ACCESS_DENIED:
      fprintf(stderr,"[ERROR] Read access denied for file '%s'.\n",string);
      break;
    case FILE_WRITE_ACCESS_DENIED:
      fprintf(stderr,"[ERROR] Write access denied for file '%s'.\n",string);
      break;
		default:
			fprintf(stderr,"[ERROR] An unknown error occured.\n");
			break;
  }
}
