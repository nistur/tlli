#include "maths.h"

tlliValue* tlli_Add(int num, tlliValue** args)
{
	int val = 0;
	for(int i = 0; i < num; ++i)
	{
		int v = 0;
		tlliValueToInt(args[i], &v);
		val += v;
	}

	tlliValue* rtn;
	tlliIntToValue(val, &rtn);
	return rtn;
}