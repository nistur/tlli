#ifndef __TLLI_INTERNAL_H__
#define __TLLI_INTERNAL_H__

#include "tlli.h"
#include "../util/map.h"

/***************************************
 * 
 ***************************************/
typedef enum
{
    TLLI_VAL_NIL = 0x00,
    TLLI_VAL_BOOL= 0x01,
    TLLI_VAL_INT = 0x02,
    TLLI_VAL_NUM = 0x03,
    TLLI_VAL_STR = 0x04,
    TLLI_VAL_PTR = 0x05,
    TLLI_VAL_LIST= 0x06,
    TLLI_VAL_FN  = 0x0F,
    TLLI_VAL_CFN = 0xFF,
} tlliValueType;

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tlliContext
{
	map* symbolTable;
};

/***************************************
 * 
 ***************************************/
struct _tlliValue
{
	unsigned int  ref;
	unsigned char type;
	void* data;
};

/***************************************
 * 
 ***************************************/
typedef struct _tlliListNode
{
    tlliValue* data;
    struct _tlliListNode* next;
} tlliListNode;

/***************************************
 * 
 ***************************************/
typedef struct _tlliCFunction
{
	tlliFn function;
} tlliCFunction;

/***************************************
 * 
 ***************************************/
typedef struct _tlliFunction
{
	char** paramlist;
	char*  doc;
	char** funcTokens;
} tlliFunction;

/***************************************
 * 
 ***************************************/
void tlliInitStaticValues();

/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#define tlliMalloc(x) (x*)malloc(sizeof(x))
#define tlliMallocArray(x,n) (x*)malloc(((int)n) * sizeof(x))
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

/***************************************
 * 
 ***************************************/
#ifndef NULL
# define NULL 0
#endif

/***************************************
 * 
 ***************************************/
#ifndef MAX
# define MAX(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef MIN
# define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#endif/*__TLLI_INTERNAL_H__*/
