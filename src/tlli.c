#include "tlli_internal.h"
#include <string.h>
#include <stdio.h>

tlliReturn tlliClearContext(tlliContext* context)
{
    tlliReturn(SUCCESS);
}

tlliReturn tlliInitContext(tlliContext** context)
{
    if(context == 0 )
        tlliReturn(NO_CONTEXT);
    *context = tlliMalloc(tlliContext);
    if(tlliClearContext(*context) != TLLI_SUCCESS)
        tlliTerminateContext(context);
    tlliReturn(SUCCESS);
}

tlliReturn tlliTerminateContext(tlliContext** context)
{
    if(*context == 0)
        tlliReturn(NO_CONTEXT);
    
    tlliFree(*context);
    *context = 0;
    tlliReturn(SUCCESS);
}

tlliReturn tlliEvaluate(tlliContext* context, const char* str, tlliValue** rtn)
{
    if(context == 0)
        tlliReturn(NO_CONTEXT);

    if(str == 0)
        tlliReturn(NO_INPUT);

    if(rtn != 0)
    {
        *rtn = tlliMalloc(tlliValue);
        (*rtn)->type = TLLI_VAL_NIL;
        (*rtn)->data = 0;
    }

    tlliReturn(SUCCESS);
}

tlliReturn tlliValueToString(tlliValue* val, char** str, int size)
{
    if(val == 0 || str == 0)
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
    }

    memcpy(*str, buffer, MIN(size, strlen(buffer)));

    tlliReturn(SUCCESS);
}

tlliReturn tlliTerminateValue(tlliValue** value)
{
    if(value == 0)
        tlliReturn(NO_INPUT);

    tlliFree((*value)->data);

    tlliFree(*value);
    *value = 0;
    tlliReturn(SUCCESS);
}

const char* tlliError()
{
    return g_tlliErrors[g_tlliError];
}
