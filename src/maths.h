#ifndef __TLLI_MATHS_H__
#define __TLLI_MATHS_H__

#include "tlli.h"

tlliValue* tlli_Add(int num, tlliValue** args);
tlliValue* tlli_Sub(int num, tlliValue** args);
tlliValue* tlli_Mul(int num, tlliValue** args);
tlliValue* tlli_Div(int num, tlliValue** args);

#endif/*__TLLI_MATHS_H__*/