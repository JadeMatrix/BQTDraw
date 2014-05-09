#ifndef BQT_MUTEX_HPP
#define BQT_MUTEX_HPP

/* 
 * bqt_mutex.hpp
 * 
 * Contains bqt::mutex, a class definition for manipulating & managing mutices
 * as objects.  Conditions need private access to mutices to access the internal
 * pthreads data, so bqt::condition is marked as a friend class in bqt::mutex.
 * Also contains bqt::scoped_lock, a superior way to use mutices compared to
 * lock()/unlock() blocks.  It is safe to wait a condition on a scope-locked
 * mutex.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_threadutil.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class mutex
    {
        friend class condition;
    protected:
        pthread_mutex_t pt_mutex;
    public:
        mutex();
        ~mutex();
        
        // These need to be const to allow thread-safety as well as const-safety in data types
        void lock() const;
        void unlock() const;
        bool try_lock() const;                                                  // Returns true if lock was successful, false if it was not.
    };
    
    class scoped_lock
    {
    private:
        mutex& slm;
    public:
        scoped_lock( mutex& m ) : slm( m )
        {
            slm.lock();
        }
        ~scoped_lock()
        {
            slm.unlock();
        }
    };
}

/******************************************************************************//******************************************************************************/

#endif


