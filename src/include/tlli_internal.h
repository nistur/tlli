#pragma once
#ifndef __TLLI_INTERNAL_H__
#define __TLLI_INTERNAL_H__

#include "tlli.h"

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tlliContext
{
};

struct _tlliValue
{
};

/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#define tlliMalloc(x) (x*)malloc(sizeof(x))
#define tlliFree(x)   free(x)

/***************************************
 * Error handling
 ***************************************/
extern tlliReturn  g_tlliError;
extern const char* g_tlliErrors[];
#define tlliReturn(x)				\
    {						\
	g_tlliError = TLLI_##x;			\
	return TLLI_##x;			\
    }



#endif/*__TLLI_INTERNAL_H__*/
