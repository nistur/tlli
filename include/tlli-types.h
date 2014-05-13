#ifndef __TLLI_TYPES_H__
#define __TLLI_TYPES_H__

#if TLLI_USE_DOUBLE
typedef double number;
#else
typedef float number;
#endif

TLLI_EXPORT tlliReturn tlliValueToNumber   (tlliValue* val, number* num);
TLLI_EXPORT tlliReturn tlliNumberToValue   (number num, tlliValue** val);

TLLI_EXPORT tlliReturn tlliValueToInt      (tlliValue* val, int* num);
TLLI_EXPORT tlliReturn tlliIntToValue      (int num, tlliValue** val);

TLLI_EXPORT tlliReturn tlliValueToString   (tlliValue* val, char** str, int size);
TLLI_EXPORT tlliReturn tlliStringToValue   (char* str, tlliValue** val);

TLLI_EXPORT tlliReturn tlliReleaseValue  (tlliValue** value);

extern tlliValue* tlliNil;
extern tlliValue* tlliTrue;
extern tlliValue* tlliFalse;


#endif/*__TLLI_TYPES_H__*/