#include "tlli_internal.h"

tlliReturn tlliListAddValue(tlliValue* list, tlliValue* val)
{
    if(list == 0 || val == 0)
        tlliReturn(NO_INPUT);
    if(list->type != TLLI_VAL_LIST)
        tlliReturn(PARSE_ERR); // need a type error

    tlliListNode** node = (tlliListNode**)&(list->data);
    while(*node)
    {
        node = &((*node)->next);
    }
    *node = tlliMalloc(tlliListNode);
    (*node)->data = val;

    tlliRetainValue(val);
    
    tlliReturn(SUCCESS);
}

tlliReturn tlliListAddFront(tlliValue* list, tlliValue* val)
{
    if(list == 0 || val == 0)
        tlliReturn(NO_INPUT);
    if(list->type != TLLI_VAL_LIST)
        tlliReturn(PARSE_ERR); // need a type error

    tlliListNode* node = tlliMalloc(tlliListNode);
    node->data = val;
    node->next = list->data;
    list->data = node;
    
    tlliRetainValue(val);
    
    tlliReturn(SUCCESS);
}

tlliReturn tlliListRemove(tlliValue* list, tlliValue* val)
{
    if(list == 0 || val == 0)
        tlliReturn(NO_INPUT);
    if(list->type != TLLI_VAL_LIST)
        tlliReturn(PARSE_ERR); // need a type error

    tlliListNode** node = (tlliListNode**)&(list->data);
    while(*node)
    {
        if((*node)->data == val)
        {
            tlliListNode* foundNode = *node;
            *node = foundNode->next;
            tlliReleaseValue(&val);
            tlliFree(foundNode);
            tlliReturn(SUCCESS);
        }
    }
    
    tlliReturn(INVALID);
}
