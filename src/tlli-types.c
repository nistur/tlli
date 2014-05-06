#include "tlli.h"
#include "tlli_internal.h"

#include <stdio.h>
#include <string.h>

tlliReturn tlliValueToInt(tlliValue* val, int* num)
{
    if(val == NULL || num == NULL)
        tlliReturn(NO_INPUT);

    switch(val->type)
    {
   	case TLLI_VAL_NIL:
   		*num = 0;
   		break;
    case TLLI_VAL_INT:
    	*num = *(int*)val->data;
    	break;
    }

    tlliReturn(SUCCESS);
}

tlliReturn tlliIntToValue(int num, tlliValue** val)
{
    if(val == NULL)
        tlliReturn(NO_INPUT);

	*val = tlliMalloc(tlliValue);
	(*val)->type = TLLI_VAL_INT;
	(*val)->data = tlliMalloc(int);
	*((int*)(*val)->data) = num;

    tlliReturn(SUCCESS);
}

tlliReturn tlliValueToString(tlliValue* val, char** str, int size)
{
    if(val == NULL || str == NULL)
        tlliReturn(NO_INPUT);

    static char buffer[256];
    switch(val->type)
    {
    case TLLI_VAL_NIL:
        sprintf(buffer, "nil");
        break;
    case TLLI_VAL_BOOL:
        sprintf(buffer, "%s", (*(char*)val->data) ? "t" : "f");
        break;
    case TLLI_VAL_INT:
        sprintf(buffer, "%d", (*(int*)val->data));
        break;
    case TLLI_VAL_STR:
        sprintf(buffer, "%s", (char*)val->data);
        break;
    case TLLI_VAL_FN:
        sprintf(buffer, "function");
        break;
    }

    memcpy(*str, buffer, MIN(size, strlen(buffer) + 1));

    tlliReturn(SUCCESS);
}

tlliReturn tlliStringToValue(char* str, tlliValue** val)
{
	if(val == NULL || str == NULL)
		tlliReturn(NO_INPUT);

	*val = tlliMalloc(tlliValue);
	(*val)->type = TLLI_VAL_STR;
	int len = strlen(str);
	(*val)->data = tlliMallocArray(char, len+1);
	memcpy((*val)->data, str, len);
	((char*)(*val)->data)[len] = '\0';

	tlliReturn(SUCCESS);
}

tlliReturn tlliReleaseValue(tlliValue** value)
{
    if(value == NULL || *value == NULL)
        tlliReturn(NO_INPUT);

    (*value)->ref--;
    if((*value)->ref == 0)
    {
	    tlliFree((*value)->data);

	    tlliFree(*value);
	}
    *value = 0;
    tlliReturn(SUCCESS);
}
