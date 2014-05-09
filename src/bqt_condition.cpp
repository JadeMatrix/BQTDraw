/* 
 * bqt_condition.cpp
 * 
 * Implements bqt::condition from bqt_condition.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_condition.hpp"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    // May need this for timed waits eventually if they are implemented
}

/******************************************************************************//******************************************************************************/

namespace bqt
{
    condition::condition()
    {
        pthread_cond_init( &pt_cond, NULL );
    }
    condition::~condition()
    {
        pthread_cond_destroy( &pt_cond );
    }

    void condition::wait( mutex& wait_mutex )
    {
        pthread_cond_wait( &pt_cond, &( wait_mutex.pt_mutex ) );
    }
    // void wait_time( ... )
    // {
    //     //
    // }
    void condition::signal()
    {
        pthread_cond_signal( &pt_cond );
    }
    void condition::broadcast()
    {
        pthread_cond_broadcast( &pt_cond );
    }
}


