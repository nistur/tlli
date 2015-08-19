#include "maths.h"
#include "tlli_internal.h"

#include <stdio.h>

tlliValue* tlli_Num_Add(int num, tlliValue** args)
{
	number val = TLLI_NUMBER_ZERO;
	int i;
	for(i = 0; i < num; ++i)
	{
		number v = TLLI_NUMBER_ZERO;
		tlliValueToNumber(args[i], &v);
		val += v;
	}

	tlliValue* rtn;
	tlliNumberToValue(val, &rtn);
	return rtn;
}

tlliValue* tlli_Int_Add(int num, tlliValue** args)
{
	int val = 0;
	int i;
	for(i = 0; i < num; ++i)
	{
		int v = 0;
		tlliValueToInt(args[i], &v);
		val += v;
	}

	tlliValue* rtn;
	tlliIntToValue(val, &rtn);
	return rtn;
}

tlliValue* tlli_Add(int num, tlliValue** args)
{
	int i;
	int allint = 1;
	for(i = 0; i < num; ++i) {
		char t = args[i]->type;
		if(t == TLLI_VAL_NUM) {
			allint = 0;
			break;
		} else if(t != TLLI_VAL_INT) {
			return tlliNil;
		}
	}
	if(allint == 0) {
		return tlli_Num_Add(num, args);
	} else {
		return tlli_Int_Add(num, args);
	}
}

tlliValue* tlli_Sub(int num, tlliValue** args)
{
	int val = 0;
	int i;
	tlliValueToInt(args[0], &val);
	for(i = 1; i < num; ++i)
	{
		int v = 0;
		tlliValueToInt(args[i], &v);
		val -= v;
	}

	tlliValue* rtn;
	tlliIntToValue(val, &rtn);
	return rtn;
}

tlliValue* tlli_Mul(int num, tlliValue** args)
{
	int val = 0;
	int i;
	tlliValueToInt(args[0], &val);
	for(i = 1; i < num; ++i)
	{
		int v = 0;
		tlliValueToInt(args[i], &v);
		val *= v;
	}

	tlliValue* rtn;
	tlliIntToValue(val, &rtn);
	return rtn;
}

tlliValue* tlli_Div(int num, tlliValue** args)
{
	int val = 0;
	int i;
	tlliValueToInt(args[0], &val);
	for(i = 1; i < num; ++i)
	{
		int v = 0;
		tlliValueToInt(args[i], &v);
		val /= v;
	}

	tlliValue* rtn;
	tlliIntToValue(val, &rtn);
	return rtn;
}
