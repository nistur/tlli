/*
 tlli.h - Public interface for the Tiny Little Lisp Interpreter

 Copyright (c) 2015 Philipp Geyer (Nistur) nistur@gmail.com

 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgement in the product documentation would be
    appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
*/


/*********************************************
 * TINY LITTLE LISP INTERPRETER
 *
 * tlli.h
 *
 * Public header.
 * No other file should be #included other
 * than this.
 *
 * Example:
 *********************************************
 * tlliContext* lisp = NULL;
 * if(TLLI_SUCCESS != tlliInitContext(&lisp))
 * {
 *     printf("TLLI Error:%s\n", tlliError());
 *     return;
 * }
 * tlliValue* rtn = NULL;
 * if(TLLI_SUCCESS == tlliEvaluate(lisp, "(+ 1 2)", &rtn))
 * {
 *     int val = 0;
 *     if(TLLI_SUCCESS == tlliValueToInt(rtn, &val))
 *     {
 *         printf("TLLI returned successfully: %d\n", val);
 *     }
 * }
 * tlliTerminateContext(&lisp);
 */

#ifndef __TLLI_H__
#define __TLLI_H__
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

/* tlliReturn
 * return type for tlli functions
 */
typedef int tlliReturn;

/* tlliContext
 * Opaque type for library context
 */
typedef struct _tlliContext tlliContext;

/* tlliValue
 * Opaque base type for values passed to/from tlli
 * use functions in tlli-types.h to convert to C types
 */
typedef struct _tlliValue   tlliValue;

/* tlliFn
 * Function type to be exposed to tlli
 */
typedef tlliValue*(*tlliFn)(int,tlliValue**);
    
/*******************************
 * RETURN CODES
 ******************************/
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
#endif/*__TLLI_H__*/
