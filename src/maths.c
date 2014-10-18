#include "maths.h"

tlliValue* tlli_Add(int num, tlliValue** args)
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
