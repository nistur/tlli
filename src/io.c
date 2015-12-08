#include "tlli_internal.h"

#include <stdio.h>

tlliValue* tlli_Print(int num, tlliValue** args)
{
	int i;
	char* buffer = tlliMallocArray(char, 256);
	for(i = 0; i < num; ++i)
	{
		tlliValueToString(args[i], buffer, 256);
		printf("%s\n", buffer);
	}
	tlliFree(buffer);
	return 0;
}
