#ifndef BQT_CONDITION_HPP
#define BQT_CONDITION_HPP

/* 
 * bqt_condition.hpp
 * 
 * Contains bqt::condition, a class definition for manipulating & managing
 * conditions as objects.  Conditions need private access to mutices to access
 * the internal pthreads data, so bqt::condition is marked as a friend class in
 * bqt::mutex.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_threadutil.hpp"
#include "bqt_mutex.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class condition
    {
    protected:
        pthread_cond_t pt_cond;
    public:
        condition();
        ~condition();
        
        void wait( mutex& wait_mutex );                                         // Unlocks wait_mutex & pauses thread; on return relocks wait_mutex & unpauses thread
        // void wait_time( ... )                                                // Timed wait, maybe implement later
        void signal();                                                          // Restart a single waiting thread
        void broadcast();                                                       // Restart all waiting threads
    };
}

/******************************************************************************//******************************************************************************/

#endif


