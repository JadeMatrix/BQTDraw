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
    #if defined PLATFORM_XWS_GNUPOSIX | defined PLATFORM_MACOSX
    
    condition::condition()
    {
        pthread_cond_init( &platform_condition.pt_cond, NULL );
    }
    condition::~condition()
    {
        pthread_cond_destroy( &platform_condition.pt_cond );
    }

    void condition::wait( mutex& wait_mutex )
    {
        pthread_cond_wait( &platform_condition.pt_cond, &( wait_mutex.platform_mutex.pt_mutex ) );
    }
    // void wait_time( ... )
    // {
    //     //
    // }
    void condition::signal()
    {
        pthread_cond_signal( &platform_condition.pt_cond );
    }
    void condition::broadcast()
    {
        pthread_cond_broadcast( &platform_condition.pt_cond );
    }
    
    #else
    
    #error "Conditions not implemented on non-POSIX platforms"
    
    #endif
}


