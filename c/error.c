#include <stdio.h>
#include "error.h"

void throwException(int error)
{
	switch(error)
	{
		case TOO_MANY_ARGS:
			printf("[ERROR] Too many args.\n");
			break;
		case ADDLINE_FAIL:
			printf("[ERROR] Could not add new line to program because realloc() failed.\n");
			break;
		default:
			printf("An unknown error occured.\n");
			break;
	}
}
