#include "tlli-tests.h"
#include "tlli.h"

TEST(InitTerminate, Basic, 0.0f,
     // initialisation
     {
       m_data.context = 0;
     },
     // cleanup
     {
       tlliTerminateContext(&m_data.context);
     },
     // test
     {
       ASSERT(m_data.context == 0);
       ASSERT(tlliInitContext(&m_data.context) == TLLI_SUCCESS);
       ASSERT(m_data.context != 0);
       ASSERT(tlliTerminateContext(&m_data.context) == TLLI_SUCCESS);
     },
     // data
     {
       tlliContext* context;
     }
     );

TEST(Evaluate, Basic, 0.0f,
     // initialisation
     {
       m_data.context = 0;
       tlliInitContext(&m_data.context);
     },
     // cleanup
     {
       tlliTerminateContext(&m_data.context);
     },
     // test
     {
       ASSERT(tlliEvaluate(0, 0, 0) != TLLI_SUCCESS);
       ASSERT(tlliEvaluate(m_data.context, 0, 0) != TLLI_SUCCESS);
       ASSERT(tlliEvaluate(0, "()", 0) != TLLI_SUCCESS);
       ASSERT(tlliEvaluate(m_data.context, "()", 0) == TLLI_SUCCESS);
     },
     // data
     {
       tlliContext* context;
     }
     );
