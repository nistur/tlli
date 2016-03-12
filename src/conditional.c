#include "tlli_internal.h"

#include <string.h>

tlliValue* tlli_LessThan(int num, tlliValue** args)
{
	number v1 = 0;
	int i;
	tlliValueToNumber(args[0], &v1);
	for(i = 1; i < num; ++i)
	{
		number vx = 0;
		tlliValueToNumber(args[i], &vx);
		// check inverse so we don't bail too early
		if(v1 >= vx)
		{
			return tlliFalse;
		}
	}
	return tlliTrue;
}

tlliValue* tlli_Equal(int num, tlliValue** args)
{
	tlliValue* v1 = args[0];

	if(num == 0)
	{
		return tlliFalse;
	}
	if(num == 1)
	{
		switch(v1->type)
		{
		case TLLI_VAL_NIL:
			return tlliFalse;
		case TLLI_VAL_BOOL:
			return *(char*)v1->data ? tlliTrue : tlliFalse;
		case TLLI_VAL_INT:
			return *(int*)v1->data ? tlliTrue : tlliFalse;
		case TLLI_VAL_NUM:
			return *(number*)v1->data ? tlliTrue : tlliFalse;
		case TLLI_VAL_STR:
			return *(char*)v1->data && strlen(v1->data) ? tlliTrue : tlliFalse;
        case TLLI_VAL_LIST:
            return tlliTrue; // a list of any length is true?
        }
		return tlliTrue;
	}
	int i;
	for(i = 1; i < num; ++i)
	{
		if(v1->type != args[i]->type)
			return tlliFalse;
		switch(v1->type)
		{
		case TLLI_VAL_NIL:
			continue;
		case TLLI_VAL_BOOL:
			if(*(char*)v1->data != *(char*)args[i]->data)
				return tlliFalse;
			break;
		case TLLI_VAL_INT:
			if(*(int*)v1->data != *(int*)args[i]->data)
				return tlliFalse;
			break;
		case TLLI_VAL_NUM:
			if(*(number*)v1->data != *(number*)args[i]->data)
				return tlliFalse;
			break;
		case TLLI_VAL_STR:
			if(strcmp((char*)v1->data, (char*)args[i]->data) != 0 )
				return tlliFalse;
		case TLLI_VAL_FN:
		case TLLI_VAL_CFN: 
			if(v1->data != args[i]->data)
				return tlliFalse;
        case TLLI_VAL_LIST:
        {
            tlliListNode* n1 = 0;
            tlliListNode* n2 = 0;
            tlliValue* lv[2];
            
            if(args[i]->type != TLLI_VAL_LIST)
                return tlliFalse;
            while(1)
            {
                tlliReturn r1 = tlliListNext(v1, &n1, &lv[0]);
                tlliReturn r2 = tlliListNext(args[i], &n2, &lv[2]);
                if(r1 != r2)
                    return tlliFalse; // if they both fail, that's fine

                if(r1 == TLLI_OUT_OF_BOUNDS)
                    break;

                if(r1 == TLLI_SUCCESS &&
                   tlli_Equal(2, lv) == tlliFalse)
                    return tlliFalse;
                
                // if we get here, we're either in an error state
                // which we cannot handle, or we're successful, so
                // move onto the next entry
            }
        }
		}
	}

	return tlliTrue;
}
