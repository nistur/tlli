#include "tlli_internal.h"
#include <stdio.h>
#include <string.h>

typedef struct _tlliScope
{
    map*               m_values;
    struct _tlliScope* m_parent;
} tlliScope;

tlliReturn tlliScopeGetValue(tlliScope* scope, const char* name, tlliValue** val)
{
    *val = MapGet(scope->m_values, name);
    if(*val)
	tlliReturn(SUCCESS);

    if(scope->m_parent)
	return tlliScopeGetValue(scope->m_parent, name, val);
    tlliReturn(INVALID);
}

tlliReturn tlliScopeNew(tlliScope** scope, tlliScope* parent)
{
    *scope = tlliMalloc(tlliScope);
    (*scope)->m_parent = parent;
    (*scope)->m_values = InitMap();

    tlliReturn(SUCCESS);
}

tlliReturn tlliScopeFree(tlliScope** scope)
{
    TerminateMap(&(*scope)->m_values);
}

char* tlliStrTok(char* str, char** lasts);

tlliReturn tlliEvaluateList(tlliContext* context, tlliValue* list, tlliValue** rtn, tlliValue** scope)
{
    tlliReturn(SUCCESS);
}

tlliReturn tlliParseToken(tlliContext* context, char* token, tlliValue** sym, tlliValue** scope)
{
    tlliReturn(SUCCESS);
}

tlliReturn tlliParseInternal(tlliContext* context, char* str, char** last, tlliValue** list)
{
    char* tok;
    tlliListNewList(list);

    if(*last == NULL)
    {
	tok = tlliStrTok(str, last);
	if(strcmp(tok, "(") != 0)
	{
	    tlliReturn(NO_INPUT);
	}
    }

    int quote = 0;
    for(tok = tlliStrTok(NULL, last); tok; tok = tlliStrTok(NULL, last))
    {
	int shouldQuote = quote;
	quote = 0;
	if(strcmp(tok, "'") == 0)
	{
	    quote = 1;
	    continue;
	}
	else if(strcmp(tok, "(") == 0)
	{
	    tlliValue* subList = NULL;
	    tlliParseInternal(context, str, last, &subList);
	    if(shouldQuote)
	    {
		tlliListAddBack(*list, subList);
	    }
	    else
	    {
		tlliValue* ret = NULL;
		tlliEvaluateList(context, subList, &ret);
		tlliListAddBack(*list, ret);
	    }
	    continue;
	}
	else if(strcmp(tok, ")") == 0)
	{
	    break;
	}
	else
	{
	    tlliValue* sym = NULL;
	    tlliParseToken(context, tok, &sym);
	    tlliListAddBack(*list, sym);
	}
    }
 
    tlliReturn(SUCCESS);
}

tlliReturn tlliParseList(tlliContext* context, char* str, tlliValue** list)
{
//    char** tokens = NULL;
    char* last = NULL;
    tlliValue* ret;
    
    tlliParseInternal(context, str, &last, list);

    tlliEvaluateList(context, *list, &ret);

    tlliReturn(SUCCESS);
}
