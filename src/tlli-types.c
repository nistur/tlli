#include "tlli.h"
#include "tlli_internal.h"

#include <stdio.h>
#include <string.h>

tlliValue* tlliNil;
tlliValue* tlliTrue;
tlliValue* tlliFalse;

void tlliInitStaticValues()
{
    if(tlliNil == NULL)
    {
        tlliValue* val = tlliMalloc(tlliValue);
        val->type = TLLI_VAL_NIL;
        val->data = NULL;
        tlliNil = val;
    }

    if(tlliTrue == NULL)
    {
        tlliValue* val = tlliMalloc(tlliValue);
        val->type = TLLI_VAL_BOOL;
        val->data = tlliMalloc(char);
        *(char*)val->data = 1;
        tlliTrue = val;
    }

    if(tlliFalse == NULL)
    {
        tlliValue* val = tlliMalloc(tlliValue);
        val->type = TLLI_VAL_BOOL;
        val->data = tlliMalloc(char);
        *(char*)val->data = 0;
        tlliFalse = val;
    }
}

tlliReturn tlliValueToNumber(tlliValue* val, number* num)
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
    case TLLI_VAL_NUM:
        *num = *(number*)val->data;
        break;
    default:
        tlliReturn(INVALID);
    }

    tlliReturn(SUCCESS);
}

tlliReturn tlliNumberToValue(number num, tlliValue** val)
{
    if(val == NULL)
        tlliReturn(NO_INPUT);

    *val = tlliMalloc(tlliValue);
    (*val)->type = TLLI_VAL_NUM;
    (*val)->data = tlliMalloc(number);
    *((number*)(*val)->data) = num;

    tlliReturn(SUCCESS);
}

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
    case TLLI_VAL_NUM:
        *num = *(number*)val->data;
        break;
    default:
        tlliReturn(INVALID);
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

tlliReturn tlliValueToString(tlliValue* val, char* str, int size)
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
    case TLLI_VAL_NUM:
#ifdef TLLI_USE_DOUBLE
        sprintf(buffer, "%lf", *(number*)val->data);
#else
        sprintf(buffer, "%f", *(number*)val->data);
#endif
        break;
    case TLLI_VAL_STR:
        sprintf(buffer, "%s", (char*)val->data);
        break;
    case TLLI_VAL_PTR:
        sprintf(buffer, "0x%X", (unsigned int)*(pointer*)val->data);
        break;
    case TLLI_VAL_FN:
    case TLLI_VAL_CFN:
        sprintf(buffer, "function");
        break;
    case TLLI_VAL_LIST:
    {
        char tmp[256];
        char index = 0;
        tlliListNode* node = val->data;
        while(node)
        {
            if(tlliValueToString(node->data, &tmp[index], 256-index) !=
               TLLI_SUCCESS)
            {
                return g_tlliError;
            }
            int len = strlen(tmp[index]);
            index += len;
            node = node->next;
            if(node)
            {
                sprintf(&tmp[index], ", ");
                index += 2;
            }
        }
        sprintf(buffer, "(%s)", tmp);
    }
    }

    memcpy(str, buffer, MIN(size, strlen(buffer) + 1));

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


tlliReturn tlliValueToPointer(tlliValue* val, pointer* ptr)
{
    if(val == NULL || ptr == NULL)
        tlliReturn(NO_INPUT);

    if(val->type != TLLI_VAL_PTR)
        tlliReturn(INVALID);
    
    *ptr = *((pointer*)val->data);
    
    tlliReturn(SUCCESS);
}

tlliReturn tlliPointerToValue(pointer ptr, tlliValue** val)
{
    if(val == NULL)
        tlliReturn(NO_INPUT);

	*val = tlliMalloc(tlliValue);
    if(*val == NULL)
        tlliReturn(OUT_OF_MEM);
	(*val)->type = TLLI_VAL_PTR;
	(*val)->data = tlliMalloc(pointer);
    if((*val)->data == NULL)
    {
        tlliFree(*val);
        tlliReturn(OUT_OF_MEM);
    }

	*((pointer*)(*val)->data) = ptr;

    tlliReturn(SUCCESS);
}

tlliReturn tlliRetainValue(tlliValue* value)
{
	if(value == NULL) tlliReturn(NO_INPUT);

	value->ref++;
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
