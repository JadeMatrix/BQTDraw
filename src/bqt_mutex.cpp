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
    #if defined PLATFORM_XWS_GNUPOSIX | defined PLATFORM_MACOSX
    
    mutex::mutex()
    {
        if( pthread_mutexattr_init( &platform_mutex.pt_attr ) )
            throw exception( "mutex::mutex(): Could not initialize mutex attributes" );
        
        if( pthread_mutexattr_settype( &platform_mutex.pt_attr, PTHREAD_MUTEX_RECURSIVE ) )
            throw exception( "mutex::mutex(): Recursive muteces not available" );
        
        if( pthread_mutex_init( &platform_mutex.pt_mutex, &platform_mutex.pt_attr ) )
            throw exception( "mutex::mutex(): Could not create mutex" );
    }
    mutex::~mutex()
    {
        pthread_mutex_destroy( &platform_mutex.pt_mutex );
        pthread_mutexattr_destroy( &platform_mutex.pt_attr );
    }
    void mutex::lock() const
    {
        if( pthread_mutex_lock( const_cast< pthread_mutex_t* >( &platform_mutex.pt_mutex ) ) )
            throw exception( "mutex::lock(): Failed to lock mutex" );
    }
    void mutex::unlock() const
    {
        if( pthread_mutex_unlock( const_cast< pthread_mutex_t* >( &platform_mutex.pt_mutex ) ) )
            throw exception( "mutex::unlock(): Failed to unlock mutex" );
    }
    bool mutex::try_lock() const
    {
        if( pthread_mutex_trylock( const_cast< pthread_mutex_t* >( &platform_mutex.pt_mutex ) ) )
            return true;
        else
            return false;
    }
    
    #else
    
    #error "Muteces not implemented on non-POSIX platforms"
    
    #endif
}


