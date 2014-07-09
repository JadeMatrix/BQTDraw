/* 
 * bqt_mutex.cpp
 * 
 * Implements bqt::mutex from bqt_mutex.hpp; bqt::scoped_lock is trivial and is
 * implemented in bqt_mutex.hpp.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_mutex.hpp"

#include "bqt_exception.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    mutex::mutex()
    {
        if( pthread_mutexattr_init( &pt_attr ) )
            throw exception( "mutex::mutex(): Could not initialize mutex attributes" );
        
        if( pthread_mutexattr_settype( &pt_attr, PTHREAD_MUTEX_RECURSIVE ) )
            throw exception( "mutex::mutex(): Recursive muteces not available" );
        
        if( pthread_mutex_init( &pt_mutex, &pt_attr ) )
            throw exception( "mutex::mutex(): Could not create mutex" );
    }
    mutex::~mutex()
    {
        pthread_mutex_destroy( &pt_mutex );
        pthread_mutexattr_destroy( &pt_attr );
    }
    void mutex::lock() const
    {
        if( pthread_mutex_lock( const_cast< pthread_mutex_t* >( &pt_mutex ) ) )
            throw exception( "mutex::lock(): Failed to lock mutex" );
    }
    void mutex::unlock() const
    {
        if( pthread_mutex_unlock( const_cast< pthread_mutex_t* >( &pt_mutex ) ) )
            throw exception( "mutex::unlock(): Failed to unlock mutex" );
    }
    bool mutex::try_lock() const
    {
        if( pthread_mutex_trylock( const_cast< pthread_mutex_t* >( &pt_mutex ) ) )
            return true;
        else
            return false;
    }
}


