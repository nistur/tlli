#pragma once
#ifndef __TLLI_INTERNAL_H__
#define __TLLI_INTERNAL_H__

#include "tlli.h"

#define TLLI_VAL_NIL  0
#define TLLI_VAL_BOOL 1
#define TLLI_VAL_INT  2

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tlliContext
{
};

struct _tlliValue
{
	unsigned char type;
	void* data;
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


#ifndef MAX
# define MAX(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef MIN
# define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#endif/*__TLLI_INTERNAL_H__*/
