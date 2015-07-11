//#pragma once
#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

#ifdef TLLI_DYNAMIC
# ifdef WIN32
#  ifdef TLLI_BUILD
#   define TLLI_EXPORT __declspec( dllexport )
#  else
#   define TLLI_EXPORT __declspec( dllimport )
#  endif
# endif
#endif
 
#ifndef TLLI_EXPORT
# define TLLI_EXPORT
#endif

typedef int tlliReturn;

typedef struct _tlliContext tlliContext;
typedef struct _tlliValue   tlliValue;

typedef tlliValue*(*tlliFn)(int,tlliValue**);

#define TLLI_SUCCESS    0
#define TLLI_NO_CONTEXT 1
#define TLLI_NO_INPUT   2
#define TLLI_OUT_OF_MEM 3
#define TLLI_PARSE_ERR  4

TLLI_EXPORT tlliReturn tlliInitContext     (tlliContext** context);
TLLI_EXPORT tlliReturn tlliTerminateContext(tlliContext** context);
TLLI_EXPORT tlliReturn tlliEvaluate        (tlliContext*  context, char* str, tlliValue** rtn);
TLLI_EXPORT tlliReturn tlliAddValue 	   (tlliContext*  context, const char* name, tlliValue* val);
TLLI_EXPORT tlliReturn tlliAddFunction     (tlliContext*  context, const char* name, tlliFn function);

#include "tlli-types.h"

TLLI_EXPORT const char*  tlliError();

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TEMPLATE_H__*/
