#ifndef BQT_THREADUTIL_HPP
#define BQT_THREADUTIL_HPP

/* 
 * bqt_threadutil.hpp
 * 
 * Utilities file for concurrency wrappers
 * Currently using pthreads
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <pthread.h>

/******************************************************************************//******************************************************************************/

namespace bqt
{
    // class thread;
    // class mutex;
    // class condition;
    // class semaphore;
    // //class rwlock;
    // //class spinlock;
    
    typedef void* (* thread_func)( void* );
    typedef void* exit_code;
    
    // Recognized exit codes
    // Definitions so main() can use them too
    #define EXIT_FINE    0x00
    #define EXIT_INITERR 0x01
    #define EXIT_BQTERR  0x02
    #define EXIT_STDERR  0x03
    #define EXIT_ARREST  0x04
    static exit_code EXITCODE_FINE    = ( void* )EXIT_FINE;
    static exit_code EXITCODE_INITERR = ( void* )EXIT_INITERR;
    static exit_code EXITCODE_BQTERR  = ( void* )EXIT_BQTERR;
    static exit_code EXITCODE_STDERR  = ( void* )EXIT_STDERR;
    static exit_code EXITCODE_ARREST  = ( void* )EXIT_ARREST;
    
    long getSystemCoreCount();
}

/******************************************************************************//******************************************************************************/

#endif


