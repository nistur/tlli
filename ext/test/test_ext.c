#include <stdio.h>
#include "tlli.h"

tlliValue* testFunc(int nparams, tlliValue** params)
{
    printf("test output\n");
    return tlliNil;
}

void tlliInit(tlliContext* context)
{
    printf("Init extension\n");
    
    tlliAddFunction(context, "test-print", testFunc);
}

void tlliTerminate(tlliContext* context)
{
    printf("Terminate extension\n");
}
