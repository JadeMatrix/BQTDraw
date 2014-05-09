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
        pthread_mutex_init( &pt_mutex, NULL );
    }
    mutex::~mutex()
    {
        pthread_mutex_destroy( &pt_mutex );
    }
    void mutex::lock() const
    {
        if( pthread_mutex_lock( const_cast< pthread_mutex_t* >( &pt_mutex ) ) )
            throw exception( "bqt::mutex::lock(): Failed to lock mutex" );
    }
    void mutex::unlock() const
    {
        if( pthread_mutex_unlock( const_cast< pthread_mutex_t* >( &pt_mutex ) ) )
            throw exception( "bqt::mutex::unlock(): Failed to unlock mutex" );
    }
    bool mutex::try_lock() const
    {
        if( pthread_mutex_trylock( const_cast< pthread_mutex_t* >( &pt_mutex ) ) )
            return true;
        else
            return false;
    }
}


