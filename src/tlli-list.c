#include "tlli_internal.h"

tlliReturn tlliListAddBack(tlliValue* list, tlliValue* val)
{
    if(list == 0 || val == 0)
        tlliReturn(NO_INPUT);
    if(list->type != TLLI_VAL_LIST)
        tlliReturn(TYPE_ERR);

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
        tlliReturn(TYPE_ERR);

    tlliListNode* node = tlliMalloc(tlliListNode);
    node->data = val;
    node->next = list->data;
    list->data = node;
    
    tlliRetainValue(val);
    
    tlliReturn(SUCCESS);
}

tlliReturn tlliListInsert(tlliValue* list, unsigned int n, tlliValue* val)
{
    if(list == 0 || val == 0)
        tlliReturn(NO_INPUT);
    if(list->type != TLLI_VAL_LIST)
        tlliReturn(TYPE_ERR);

    tlliListNode** node = (tlliListNode**)&(list->data);
    unsigned int i = 0;
    while(*node && i <= n)
    {
        *node = (*node)->next;
        ++i;
    }

    if(i != n)
        tlliReturn(OUT_OF_BOUNDS);
    tlliListNode* newNode = tlliMalloc(tlliListNode);
    newNode->data = val;
    tlliRetainValue(val);

    newNode->next = (*node)->next;
    *node = newNode;

    tlliReturn(SUCCESS);
}

tlliReturn tlliListRemove(tlliValue* list, tlliValue* val)
{
    if(list == 0 || val == 0)
        tlliReturn(NO_INPUT);
    if(list->type != TLLI_VAL_LIST)
        tlliReturn(TYPE_ERR);

    tlliListNode** node = (tlliListNode**)&(list->data);
    while(*node)
    {
        tlliValue* vals[2];
        vals[0] = (*node)->data;
        vals[1] = val;
        if(tlli_Equal(2, vals) == tlliTrue)
        {
            tlliListNode* foundNode = *node;
            *node = foundNode->next;
            tlliReleaseValue(&val);
            tlliFree(foundNode);
            tlliReturn(SUCCESS);
        }
        else
        {
            node = &(*node)->next;
        }
    }
    
    tlliReturn(INVALID);
}

tlliReturn tlliListNth(tlliValue* list, unsigned int n, tlliValue** val)
{
    if(list == 0 || val == 0)
        tlliReturn(NO_INPUT);
    if(list->type != TLLI_VAL_LIST)
        tlliReturn(TYPE_ERR);

    tlliListNode** node = (tlliListNode**)&(list->data);
    unsigned int i = 0;
    while(*node && i <= n)
    {
        node = &(*node)->next;
        ++i;
    }

    if(i == n)
    {
        *val = (*node)->data;
    }
    else
    {
        tlliReturn(OUT_OF_BOUNDS);
    }
    
    tlliReturn(SUCCESS);
}

tlliReturn tlliListNext(tlliValue* list, tlliListNode** node, tlliValue** val)
{
    if(node == 0 || val == 0 ||
       (list == 0 && *node == 0)) // at lease one of these needs data
        tlliReturn(NO_INPUT);
    if(list->type != TLLI_VAL_LIST)
        tlliReturn(TYPE_ERR);

    if(*node == 0)
        *node = (tlliListNode*)list->data;
    else
        *node = (*node)->next;

    if(*node == 0)
        tlliReturn(OUT_OF_BOUNDS);

    *val = (*node)->data;
        
    tlliReturn(SUCCESS);
}
