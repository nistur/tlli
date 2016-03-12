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
typedef enum
{
    TLLI_SUCCESS,
    TLLI_NO_CONTEXT,
    TLLI_NO_INPUT,
    TLLI_OUT_OF_MEM,
    TLLI_PARSE_ERR,
    TLLI_TYPE_ERR,
    TLLI_OUT_OF_BOUNDS,
    TLLI_INVALID,
} tlliReturn;

/* tlliInitContext
 *   Initialises an instance of the tlli library. Will set up the lisp environment
 * params:
 *   context - The context to set up
 * returns:
 *   TLLI_SUCCESS    - The context was initialised successfully
 *   TLLI_NO_CONTEXT - NULL context was provided 
 */
TLLI_EXPORT tlliReturn tlliInitContext     (tlliContext** context);

/* tlliTerminateContext
 *   Cleans up an instance of the tlli library. Will release all allocated memory
 * params:
 *   context - The context to clean up
 * returns:
 *   TLLI_SUCCESS    - The context was cleaned up sucessfully
 *   TLLI_NO_CONTEXT - NULL context was provided
 */    
TLLI_EXPORT tlliReturn tlliTerminateContext(tlliContext** context);

/* tlliEvaluate
 *   Evaluates a null terminated string containing tlli lisp.
 * params:
 *   context - The context in which to evaluate the string.
 *   str     - The string to evaluate
 *   rtn     - Optional return value
 * returns:
 *   TLLI_SUCCESS    - The string was evaluated successfully
 *   TLLI_NO_CONTEXT - NULL context was provided
 *   TLLI_NO_INPUT   - NULL input string given
 */    
TLLI_EXPORT tlliReturn tlliEvaluate        (tlliContext*  context, char* str, tlliValue** rtn);

/* tlliAddValue
 *   Adds a value to the environment with a given name
 * params:
 *   context - The context to which to add the value to
 *   name    - The symbol name to assign the value to
 *   val     - The value to add to the context
 * returns:
 *   TLLI_SUCCESS    - The value was added successfully
 *   TLLI_NO_CONTEXT - NULL context was provided
 *   TLLI_NO_INPUT   - NULL value provided
 * Note:
 *   I am aware that this isn't necessarily in the spirit of functional programming
 * but it helps with debugging on occasion, so I've left it in
 */
TLLI_EXPORT tlliReturn tlliAddValue 	   (tlliContext*  context, const char* name, tlliValue* val);

/* tlliAddFunction
 *   Adds a C-function to the environment with a given name
 * params:
 *   context  - The context to which to add the function to
 *   name     - The symbol name to assign the function to
 *   function - The function to add to the context
 * returns:
 *   TLLI_SUCCESS    - The function was added sucessfully
 *   TLLI_NO_CONTEXT - NULL context was provided
 *   TLLI_NO_INPUT   - NULL function pointer provided
 */    
TLLI_EXPORT tlliReturn tlliAddFunction     (tlliContext*  context, const char* name, tlliFn function);

/**************
 * TLLI TYPES *
 **************/    
#include "tlli-types.h"

/**************
 * TLLI LISTS *
 **************/    
#include "tlli-list.h"
    
/* tlliError
 *   Returns a human-readable error message for the last TLLI function called
 */    
TLLI_EXPORT const char*  tlliError();
    
#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TLLI_H__*/
