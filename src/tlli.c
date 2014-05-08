#include "tlli_internal.h"

#include "util/stb.h"
#include "maths.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

// reimplementation of strtok_r but without
// the `sep` param as it should tokenise
// (banana "mushroom potato")
// as the following 4 tokens:
// 1 - (
// 2 - banana
// 3 - mushroom potato
// 4 - )
char* tlliStrTok(char* str, char** lasts)
{
    char* start;
    char* rtn;
    if(str)
        start = str;
    else
        start = *lasts;

    while(isspace(*start))
        ++start;
    if(start == NULL || *start == '\0')
        return NULL;
    if(*start == '(' || *start == ')' || *start == '\'')
    {
        rtn = tlliMallocArray(char, 2);
        rtn[0] = *start; rtn[1] = '\0';
        *lasts = start + 1;
        return rtn;
    }

    if(*start == '"')
    {
        char* end = start + 1;
        while(*end != '"' && *end != '\0') ++end;
        int size = end - start + 2;
        rtn = tlliMallocArray(char, size);
        memcpy(rtn, start, size);
        rtn[size-1] = '\0';
        *lasts = end + 1;
        return rtn;
    }

    char* end = start + 1;
    while(!isspace(*end) && *end != ')') ++end;
    int size = end - start;
    rtn = tlliMallocArray(char, size+1);
    memcpy(rtn, start, size);
    rtn[size] = '\0';
    *lasts = end;
    return rtn;
}

tlliReturn tlliClearContext(tlliContext* context)
{
    if(context->symbolTable)
        TerminateMap(&context->symbolTable);
    context->symbolTable = InitMap();
    tlliAddFunction(context, "+", tlli_Add);
    tlliAddFunction(context, "-", tlli_Sub);
    tlliAddFunction(context, "*", tlli_Mul);
    tlliAddFunction(context, "/", tlli_Div);
    tlliReturn(SUCCESS);
}

tlliReturn tlliInitContext(tlliContext** context)
{
    if(context == 0 )
        tlliReturn(NO_CONTEXT);
    *context = tlliMalloc(tlliContext);
    (*context)->symbolTable = NULL;
    if(tlliClearContext(*context) != TLLI_SUCCESS)
        tlliTerminateContext(context);
    tlliReturn(SUCCESS);
}

tlliReturn tlliTerminateContext(tlliContext** context)
{
    if(*context == 0)
        tlliReturn(NO_CONTEXT);
    
    TerminateMap(&(*context)->symbolTable);
    tlliFree(*context);
    *context = 0;
    tlliReturn(SUCCESS);
}

tlliReturn tlliDefun(tlliContext* context, char** tokens, int* index, tlliValue** rtn)
{
    if(context == 0)
        tlliReturn(NO_CONTEXT);

    tlliValue* fn = tlliMalloc(tlliValue);
    fn->type = TLLI_VAL_FN;

    int start = *index;
    tlliFunction* functionDef = tlliMalloc(tlliFunction);

    functionDef->paramlist = NULL;
    functionDef->doc = NULL;
    functionDef->funcTokens = NULL;

    *index += 2;
    //check for fn params after the name
    if(strcmp(tokens[*index], "(") == 0)
    {
        *index += 1;
        while(strcmp(tokens[*index], ")") != 0)
        {
            int len = strlen(tokens[*index]);
            char* param = tlliMallocArray(char, len + 1);
            memcpy(param, tokens[*index], len);
            param[len] = 0;
            sbpush(functionDef->paramlist, param);
            *index += 1;
        }
    }
    *index += 1;
    // check for docstring
    if(tokens[*index][0] == '"')
    {
        int len = strlen(tokens[*index]);
        functionDef->doc = tlliMallocArray(char, len + 1);
        memcpy(functionDef->doc, tokens[*index], len);
        functionDef->doc[len] = 0;
    }

    int parenCount = 1;
    sbpush(functionDef->funcTokens, "(");
        while(parenCount > 0)
        {
            if(strcmp(tokens[*index], "(") == 0)
            {
                parenCount++;
            }
            else if(strcmp(tokens[*index], ")") == 0)
            {
                parenCount--;
            }
            int len = strlen(tokens[*index]);
            char* tok = tlliMallocArray(char, len + 1);
            memcpy(tok, tokens[*index], len);
            tok[len] = 0;
            sbpush(functionDef->funcTokens, tok);
            *index += 1;   
        }

    fn->data = functionDef;

    MapAdd(context->symbolTable, tokens[start + 1], fn);

    if(rtn)
        *rtn = fn;
    tlliReturn(SUCCESS);
}

tlliReturn tlliParseFunc(tlliContext* context, char** tokens, int* index, tlliValue** rtn, tlliValue** scope, tlliFunction* funcDef)
{
    if(strcmp(tokens[*index], "(") != 0)
        tlliReturn(PARSE_ERR);

    *index += 1;
    if(strcmp(tokens[*index], ")") == 0)
    {
        if(rtn)
        {
            *rtn = tlliMalloc(tlliValue);
            (*rtn)->type = TLLI_VAL_NIL;
            (*rtn)->data = NULL;
        }
        tlliReturn(SUCCESS);
    }
    while(strcmp(tokens[*index], "(") == 0)
    {
        tlliParseFunc(context, tokens, index, rtn, scope, funcDef);
    }

    if(strcmp(tokens[*index], "defun") == 0)
    {
        return(tlliDefun(context, tokens, index, rtn));
    }

    tlliValue* fn = MapGet(context->symbolTable, tokens[*index]);
    if(fn == NULL || (fn->type != TLLI_VAL_CFN && fn->type != TLLI_VAL_FN))
    {
        if(rtn && !*rtn)
        {
            *rtn = tlliMalloc(tlliValue);
            (*rtn)->type = TLLI_VAL_NIL;
            (*rtn)->data = NULL;
            tlliReturn(PARSE_ERR);
        }
        tlliReturn(SUCCESS);
    }

    *index += 1;
    tlliValue** params = NULL;
    while(strcmp(tokens[*index], ")") && *index < sbcount(tokens))
    {
        tlliValue* val = NULL;
        if(strcmp(tokens[*index], "(") == 0)
        {
            if(tlliParseFunc(context, tokens, index, &val, scope, funcDef) != TLLI_SUCCESS)
            {
                sbfree(params);
                if(rtn)
                {
                    *rtn = tlliMalloc(tlliValue);
                    (*rtn)->type = TLLI_VAL_NIL;
                    (*rtn)->data = NULL;
                }
                return g_tlliError;
            }
        }
        else if( tokens[*index][0] == '"' )
        {
            val = tlliMalloc(tlliValue);
            val->type = TLLI_VAL_STR;
            int len = strlen(tokens[*index]) - 1;
            val->data = tlliMallocArray(char, len);
            memcpy(val->data, &(tokens[*index][1]), len-1);
            ((char*)val->data)[len-1] = '\0';
        }
        else if( isdigit(tokens[*index][0]) )
        {
            val = tlliMalloc(tlliValue);
            val->type = TLLI_VAL_INT;
            val->data = tlliMalloc(int);
            *(int*)val->data = atoi(tokens[*index]);
        }
        else
        {
            char localVal = 0;
            if(funcDef != NULL)
            {
                for(int i = 0; i < sbcount(funcDef->paramlist); ++i)
                {
                    if(strcmp(funcDef->paramlist[i], tokens[*index]) == 0)
                    {
                        val = scope[i];
                        localVal = 1;
                    }
                }
            }
            if(localVal == 0)
            {
                val = MapGet(context->symbolTable, tokens[*index]);
            }
        }

        if(val == NULL)
        {
            if(rtn && !*rtn)
            {
                *rtn = tlliMalloc(tlliValue);
                (*rtn)->type = TLLI_VAL_NIL;
                (*rtn)->data = NULL;
            }
            sbfree(params);
            tlliReturn(PARSE_ERR);
        }
        sbpush(params, val);
        *index += 1;
    }

    tlliValue* val = NULL;
    if(fn->type == TLLI_VAL_CFN)
        val = ((tlliCFunction*)fn->data)->function(sbcount(params), params);
    else if(fn->type == TLLI_VAL_FN)
    {
        tlliFunction* fnDef = ((tlliFunction*)fn->data);
        int i = 0;
        if(tlliParseFunc(context, fnDef->funcTokens, &i, &val, params, fnDef) != TLLI_SUCCESS)
            tlliReturn(PARSE_ERR);
    }
    if(rtn)
        *rtn = val;

    tlliReturn(SUCCESS);
}

tlliReturn tlliParse(tlliContext* context, char** tokens, int* index, tlliValue** rtn)
{
    return tlliParseFunc(context, tokens, index, rtn, NULL, NULL);
}

tlliReturn tlliEvaluate(tlliContext* context, char* str, tlliValue** rtn)
{
    if(context == 0)
        tlliReturn(NO_CONTEXT);

    if(str == 0)
        tlliReturn(NO_INPUT);

    // tokenise
    char** tokens = NULL;
    char* last;
    for(char* tok = tlliStrTok(str, &last); tok; tok = tlliStrTok(NULL, &last))
    {
        sbpush(tokens, tok);
    }
    int index = 0;
    if(tlliParse(context, tokens, &index, rtn) != TLLI_SUCCESS)
    {
        sbfree(tokens);
        return g_tlliError;
    }
    sbfree(tokens);

    // if(rtn != 0)
    // {
    //     *rtn = tlliMalloc(tlliValue);
    //     (*rtn)->type = TLLI_VAL_NIL;
    //     (*rtn)->data = 0;
    // }

    tlliReturn(SUCCESS);
}

tlliReturn tlliAddFunction(tlliContext* context, const char* name, tlliFn function)
{
    if(context == 0)
        tlliReturn(NO_CONTEXT);
    if(function == 0)
        tlliReturn(NO_INPUT);

    tlliValue* fnVal = tlliMalloc(tlliValue);
    fnVal->type = TLLI_VAL_CFN;
    tlliCFunction* fn = tlliMalloc(tlliCFunction);
    fn->function = function;
    fnVal->data = fn;

    MapAdd(context->symbolTable, name, fnVal);

    tlliReturn(SUCCESS);
}

const char* tlliError()
{
    return g_tlliErrors[g_tlliError];
}
