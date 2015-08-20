#ifndef __TLLI_TYPES_H__
#define __TLLI_TYPES_H__

/* tlli can use either single or double precision floating
 * point numbers as a base 'number' type
 */
#ifdef TLLI_USE_DOUBLE
typedef double number;
#define TLLI_NUMBER_ZERO 0.0 /* Avoid implicit conversions */
#else
#define TLLI_NUMBER_ZERO 0.0f /* Avoid implicit conversions */
typedef float number;
#endif

/* tlliValueToNumber
 *   Retrieves a number (IEEE standard single- or double-precision
 * floating point number) from a tlliValue
 * params:
 *   val - The value to convert to a number
 *   num - The returned number
 * returns:
 *   TLLI_SUCCESS  - Number successfully converted
 *   TLLI_NO_INPUT - One or both of the parameters passed was NULL  
 */
TLLI_EXPORT tlliReturn tlliValueToNumber   (tlliValue* val, number* num);

/* tlliNumberToValue
 *   Creates a tlliValue from a number
 * params:
 *   num - the number to be converted to a value
 *   val - the returned value
 * returns:
 *   TLLI_SUCCESS - Number successfully converted to value
 *   TLLI_NO_INPUT - NULL value pointer passed
 * note:
 *   Returned value needs to be freed by tlliReleaseValue
 */
TLLI_EXPORT tlliReturn tlliNumberToValue   (number num, tlliValue** val);

TLLI_EXPORT tlliReturn tlliValueToInt      (tlliValue* val, int* num);
TLLI_EXPORT tlliReturn tlliIntToValue      (int num, tlliValue** val);

TLLI_EXPORT tlliReturn tlliValueToString   (tlliValue* val, char** str, int size);
TLLI_EXPORT tlliReturn tlliStringToValue   (char* str, tlliValue** val);

/* tlliRetainValue
 *   Retains a tlliValue
 * params:
 *   value - The value to retain
 * returns:
 *   TLLI_SUCCESS   - The value was retained sucessfully
 *   TLLI_NO_INPUT  - NULL value passed
 */
TLLI_EXPORT tlliReturn tlliRetainValue  (tlliValue** value);

/* tlliReleaseValue
 *   Releases a tlliValue and cleans up the memory
 * params:
 *   value - The value to clean up
 * returns:
 *   TLLI_SUCCESS  - The value was succesfully cleaned up
 *   TLLI_NO_INPUT - NULL value passed
 */
TLLI_EXPORT tlliReturn tlliReleaseValue  (tlliValue** value);

extern tlliValue* tlliNil;
extern tlliValue* tlliTrue;
extern tlliValue* tlliFalse;


#endif/*__TLLI_TYPES_H__*/
