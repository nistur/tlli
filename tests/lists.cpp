#include "tlli-tests.h"
#include "tlli.h"

TEST(NewList, Lists, 0.0f,
     // initialisation
     {
     },
     // cleanup
     {
     },
     // test
     {
         ASSERT(m_data.list == 0);
         ASSERT(tlliListNewList(&m_data.list) == TLLI_SUCCESS);
         ASSERT(m_data.list != 0);

         tlliReleaseValue(&m_data.list);

         ASSERT(tlliListNewList(0) == TLLI_NO_INPUT);
     },
     // data
     {
         tlliValue* list;
     }
     );

TEST(ListToArray, Lists, 0.0f,
     // initialisation
     {
         tlliListNewList(&m_data.list);
     },
     // cleanup
     {
         tlliReleaseValue(&m_data.list);
     },
     // test
     {
         unsigned int n = 32;
         ASSERT(tlliListToArray(m_data.list, &n, m_data.arr) == TLLI_SUCCESS);
         ASSERT(n == 0);
     },
     // data
     {
         tlliValue* list;
         tlliValue* arr[32];
     }
     );
