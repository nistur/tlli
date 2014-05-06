#ifndef __TLLI_TYPES_H__
#define __TLLI_TYPES_H__

TLLI_EXPORT tlliReturn tlliValueToInt      (tlliValue* val, int* num);
TLLI_EXPORT tlliReturn tlliIntToValue      (int num, tlliValue** val);

TLLI_EXPORT tlliReturn tlliValueToString   (tlliValue* val, char** str, int size);
TLLI_EXPORT tlliReturn tlliStringToValue   (char* str, tlliValue** val);

TLLI_EXPORT tlliReturn tlliReleaseValue  (tlliValue** value);

#endif/*__TLLI_TYPES_H__*/