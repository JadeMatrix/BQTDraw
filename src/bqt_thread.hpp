#ifndef BQT_THREAD_HPP
#define BQT_THREAD_HPP

/* 
 * bqt_thread.hpp
 * 
 * Contains bqt::thread, a class definition for manipulating & managing threads
 * as objects.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_threadutil.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class thread
    {
    protected:
        pthread_t pt_thread;
        pthread_attr_t pt_attr;
        bool has_thread;
        thread_func function;
        void* data;
        
        void createPThread( thread_func function, void* data );
        
        void kill();
    public:
        thread();
        thread( thread_func function );
        thread( void* data );
        thread( thread_func function, void* data );
        ~thread();                                                              // Cancels any currently running thread; please try to exit normally first
        
        void setFunction( thread_func function );
        void setData( void* data );
        
        bool start();
        // These do not change the stored function & data pointers
        bool start( thread_func function );
        bool start( void* data );
        bool start( thread_func function, void* data );
        
        exit_code wait();   
    };
}

/******************************************************************************//******************************************************************************/

#endif


