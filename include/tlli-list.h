#ifndef __TLLI_LISTS_H__
#define __TLLI_LISTS_H__

typedef struct _tlliListNode tlliListNode;

TLLI_EXPORT tlliReturn tlliListAddBack (tlliValue* list, tlliValue* val);
TLLI_EXPORT tlliReturn tlliListAddFront(tlliValue* list, tlliValue* val);
TLLI_EXPORT tlliReturn tlliListInsert  (tlliValue* list, unsigned int n, tlliValue* val);
TLLI_EXPORT tlliReturn tlliListInsertNext(tlliValue* list, tlliListNode* node, tlliValue* val);
TLLI_EXPORT tlliReturn tlliListRemove  (tlliValue* list, tlliValue* val);
TLLI_EXPORT tlliReturn tlliListNth     (tlliValue* list, unsigned int n, tlliValue** val);
TLLI_EXPORT tlliReturn tlliListNext    (tlliValue* list, tlliListNode** node, tlliValue** val);
TLLI_EXPORT tlliReturn tlliListNewList (tlliValue** list);
TLLI_EXPORT tlliReturn tlliListToArray (tlliValue* list, unsigned int* n, tlliValue** arr);
TLLI_EXPORT tlliReturn tlliArrayToList (tlliValue** arr, unsigned int n, tlliValue** list);
#endif/*__TLLI_LISTS_H__*/
