#include "tlli.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifdef TLLI_HAS_EXT
#include <dlfcn.h>

typedef struct _tlliExtListNode
{
    struct _tlliExtListNode* next;
    tlliValue* ext;
} tlliExtListNode;

tlliExtListNode* g_extensions;

typedef void(*tlliExtFn)();


tlliValue* tlliLoadExtension(int nparams, tlliValue** params)
{
    void* pExt = dlopen("tlli_test.so", RTLD_NOW);

    if(pExt == NULL)
        return tlliNil;

    tlliExtFn initFn = dlsym(pExt, "tlliInit");
    if(initFn == NULL)
    {
        dlclose(pExt);
        return tlliNil;
    }
    initFn();

    tlliValue* val;
    tlliPointerToValue(pExt, &val);
    tlliRetainValue(val);

    tlliExtListNode** ppListNode = &g_extensions;
    while(*ppListNode) ppListNode = &(*ppListNode)->next;
    *ppListNode = (tlliExtListNode*)malloc(sizeof(tlliExtListNode));
    (*ppListNode)->next = NULL;
    (*ppListNode)->ext = val;
    
    return val;
}

bool doUnloadExtension(tlliValue* ext)
{
    tlliExtListNode** ppListNodePrev = &g_extensions;
    tlliExtListNode* pListNodeNext = NULL;
    tlliExtListNode* pListNode = g_extensions;

    pointer pExt = NULL;
    tlliValueToPointer(ext, &pExt);
    while(pListNode)
    {
        pListNodeNext = pListNode->next;
        pointer pCheckExt = NULL;
        tlliValueToPointer(pListNode->ext, pCheckExt);
        if(pCheckExt == pExt)
        {
            tlliExtFn termFn = dlsym(pExt, "tlliTerminate");
            if(termFn != NULL)
                termFn();
            dlclose(pExt);
                
            tlliReleaseValue(&pListNode->ext);
            free(pListNode);
            *ppListNodePrev = pListNodeNext; 
            return true;
        }
        ppListNodePrev = &(*ppListNodePrev)->next;
        pListNode = pListNodeNext;        
    }
    return false;
}

tlliValue* tlliUnloadExtension(int nparams, tlliValue** params)
{
    if(nparams == 1)
    {
        doUnloadExtension(params[0]);
    }
    return tlliNil;
}

#endif/*TLLI_HAS_EXT*/

int main(int argc, char** argv)
{
	tlliContext* context = 0;
	if(tlliInitContext(&context) != TLLI_SUCCESS || context == 0)
	{
		fprintf(stderr, "Fatal error initialising TLLI\n");
		return -1;
	}

#ifdef TLLI_HAS_EXT
    if(tlliAddFunction(context, "load-extension", &tlliLoadExtension) != TLLI_SUCCESS)
    {
        fprintf(stderr, "Unable to add load-extension");
    }
#endif/*TLLI_HAS_EXT*/

	tlliValue* value = 0;
	char* buffer = malloc(256);
	while(1)
	{
		char* str = readline("tlli> ");
		if(tlliEvaluate(context, str, &value) != TLLI_SUCCESS)
		{
			tlliValueToString(value, &buffer, 256);
			fprintf(stderr, "%s\n\t%s\n", tlliError(), buffer);
			tlliReleaseValue(&value);
			continue;
		}

		tlliValueToString(value, &buffer, 256);
		printf("%s\n", buffer);
		tlliReleaseValue(&value);

	}

#ifdef TLLI_HAS_EXT
    while(g_extensions)
    {
        doUnloadExtension(g_extensions->ext);
    }
#endif/*TLLI_HAS_EXT*/

	tlliTerminateContext(&context);
	free(buffer);
	return 0;
}
