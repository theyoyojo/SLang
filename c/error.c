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
		default:
			fprintf(stderr,"[ERROR] An unknown error occured.\n");
			break;
	}
}
