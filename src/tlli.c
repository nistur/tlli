#include "tlli_internal.h"

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

    tlliReturn(SUCCESS);
}

tlliReturn tlliTerminateValue(tlliValue** value)
{
    if(value == 0)
        tlliReturn(NO_INPUT);

    tlliFree(*value);
    *value = 0;
    tlliReturn(SUCCESS);
}

const char* tlliError()
{
    return g_tlliErrors[g_tlliError];
}
