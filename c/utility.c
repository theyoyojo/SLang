#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

String newString(int size)
{
	String new;

	new.chars = (char*)malloc(sizeof(char) * size+1);
	new.length = size+1;

	return new;
}

StringString newStringString(int nStrings)
{
	StringString new;
	int i;

	new.strings = (String*)malloc(sizeof(String) * nStrings);
	new.length = nStrings;

	for(i = 0; i < nStrings; i++)
	{
		new.strings[i] = promptForString(5);
	}

	return new;
}

String promptForString(int max)
{
	int i;
	char charin;
	char* buff;
	int buffLength;
	String new;

	buff = (char*)malloc(sizeof(char)*max);
	buffLength = 0;

	printf("Enter a string, max size is %d >>",max);
	for(i = 0; i < max; i++)
	{
		scanf("%c",&charin);
		buff[i] = charin;
		buffLength++;
		if (charin == '\n')
		{
			//ungetc(charin, stdin);
			//buff[buffLength++] = '\0';
			break;
			
		}

	}
	//buff[++buffLength] = '\0';

	//clear keyboard buffer
	while(scanf("%c",&charin) == 1 && charin != '\n');

	new = newString(buffLength);
	new.length = buffLength;

	for(i = 0; i < max; i++)
	{
		new.chars[i] = '*';
	}


	for(i = 0; i < buffLength; i++)
	{
		new.chars[i] = buff[i];
	}

	return new;
}
	
void safeRealloc(void **ptr, int newSize)
{
	void *test;

	test == realloc(ptr,newSize);
	if(test == NULL)
	{
		throwException(ADDLINE_FAIL);
	}
	else
	{
		*ptr = test;
	}
}
