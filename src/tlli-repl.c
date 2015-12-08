#include "tlli.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

tlliContext* g_context;

#ifdef TLLI_HAS_EXT
#include <dlfcn.h>
#include <string.h>

#ifndef TLLI_PATH_MAX
#define TLLI_PATH_MAX 256
#endif/*TLLI_PATH_MAX*/

typedef struct _tlliExtListNode
{
    struct _tlliExtListNode* next;
    tlliValue* ext;
} tlliExtListNode;

tlliExtListNode* g_extensions;

typedef void(*tlliExtRAIIFn)(tlliContext*);

int doesFileExist(const char* file)
{
    FILE* fp = fopen(file, "r");
    if(fp)
    {
        fclose(fp);
        return 1;
    }
    return 0;
}

tlliReturn tlliFindPath(const char* ext, char* path)
{
    char* pPath = getenv("TLLI_PATH");

    char* pTok = strtok(pPath, ":");
    while(pTok)
    {
        char filepath[TLLI_PATH_MAX];
        sprintf(filepath, "%s/%s.tlli.dylib", pTok, ext);
        if(doesFileExist(filepath))
        {
            sprintf(path, "%s", filepath);
            return TLLI_SUCCESS;
        }
        pTok = strtok(NULL, ":");
    }
    return TLLI_INVALID;
}

tlliValue* tlliLoadExtension(int nparams, tlliValue** params)
{
    if(nparams != 1)
        return tlliNil;
    char extName[TLLI_PATH_MAX];
    char extPath[TLLI_PATH_MAX];

    if(tlliValueToString(params[0], extName, TLLI_PATH_MAX) != TLLI_SUCCESS)
        return tlliNil;


    if(tlliFindPath(extName, extPath) != TLLI_SUCCESS)
        return tlliNil;
    
    
    void* pExt = dlopen(extPath, RTLD_NOW);

    if(pExt == NULL)
        return tlliNil;

    tlliExtRAIIFn initFn = dlsym(pExt, "tlliInit");
    if(initFn == NULL)
    {
        dlclose(pExt);
        return tlliNil;
    }
    initFn(g_context);

    tlliValue* val;
    tlliPointerToValue(pExt, &val);
    tlliRetainValue(val);

    tlliExtListNode* pListNode = (tlliExtListNode*)malloc(sizeof(tlliExtListNode));
    pListNode->next = g_extensions;
    pListNode->ext = val;
    
    g_extensions = pListNode;

    return val;
}

tlliReturn doUnloadExtension(tlliValue* ext)
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
        tlliValueToPointer(pListNode->ext, &pCheckExt);
        if(pCheckExt == pExt)
        {
            tlliExtRAIIFn termFn = dlsym(pExt, "tlliTerminate");
            if(termFn != NULL)
                termFn(g_context);
            dlclose(pExt);
                
            tlliReleaseValue(&pListNode->ext);
            free(pListNode);
            *ppListNodePrev = pListNodeNext; 
            return TLLI_SUCCESS;
        }
        ppListNodePrev = &(*ppListNodePrev)->next;
        pListNode = pListNodeNext;        
    }
    return TLLI_INVALID;
}

tlliValue* tlliUnloadExtension(int nparams, tlliValue** params)
{
    if(nparams == 1)
    {
        if(doUnloadExtension(params[0]) == TLLI_SUCCESS)
        {
            return tlliTrue;
        }
    }
    return tlliNil;
}

#endif/*TLLI_HAS_EXT*/

int main(int argc, char** argv)
{
	if(tlliInitContext(&g_context) != TLLI_SUCCESS || g_context == 0)
	{
		fprintf(stderr, "Fatal error initialising TLLI\n");
		return -1;
	}

#ifdef TLLI_HAS_EXT
    if(tlliAddFunction(g_context, "load-extension", &tlliLoadExtension) != TLLI_SUCCESS)
    {
        fprintf(stderr, "Unable to add load-extension");
    }
    if(tlliAddFunction(g_context, "unload-extension", &tlliUnloadExtension) != TLLI_SUCCESS)
    {
        fprintf(stderr, "Unable to add unload-extension");
    }
#endif/*TLLI_HAS_EXT*/

	tlliValue* value = 0;
	char* buffer = malloc(256);
	while(1)
	{
		char* str = readline("tlli> ");
		if(tlliEvaluate(g_context, str, &value) != TLLI_SUCCESS)
		{
			tlliValueToString(value, buffer, 256);
			fprintf(stderr, "%s\n\t%s\n", tlliError(), buffer);
			tlliReleaseValue(&value);
			continue;
		}

		tlliValueToString(value, buffer, 256);
		printf("%s\n", buffer);
		tlliReleaseValue(&value);

	}

#ifdef TLLI_HAS_EXT
    while(g_extensions)
    {
        doUnloadExtension(g_extensions->ext);
    }
#endif/*TLLI_HAS_EXT*/

	tlliTerminateContext(&g_context);
	free(buffer);
	return 0;
}
