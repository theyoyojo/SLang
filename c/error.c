#include <stdio.h>
#include "error.h"

void throwException(int error)
{
	switch(error)
	{
		case TOO_MANY_ARGS:
			printf("[ERROR] Too many args.\n");
			break;
		case REALLOC_FAIL:
			printf("[ERROR] Unable to reallocate memory. Check your available RAM.\n");
			break;
		default:
			printf("[ERROR] An unknown error occured.\n");
			break;
	}
}
