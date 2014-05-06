#include "tlli.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char** argv)
{
	tlliContext* context = 0;
	if(tlliInitContext(&context) != TLLI_SUCCESS || context == 0)
	{
		printf("Fatal error initialising TLLI\n");
		return -1;
	}

	tlliValue* value;
	char* buffer = malloc(256);
	while(1)
	{
		char* str = readline("tlli> ");
		if(tlliEvaluate(context, str, &value) != TLLI_SUCCESS)
		{
			tlliValueToString(value, &buffer, 256);
			printf("%s\n\t%s\n", tlliError(), buffer);
			tlliReleaseValue(&value);
			continue;
		}

		tlliValueToString(value, &buffer, 256);
		printf("(%s)\n", buffer);
		tlliReleaseValue(&value);

	}
	tlliTerminateContext(&context);
	free(buffer);
	return 0;
}