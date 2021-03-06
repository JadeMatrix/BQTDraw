#ifndef BQT_TASK_HPP
#define BQT_TASK_HPP

/* 
 * bqt_task.hpp
 * 
 * Contains the pure virtual class bqt::task to serve as a base/interface for
 * creating custom task classes.  bqt::task uses C++'s virtual inheritance for
 * this, since any custom method would be guaranteed to be at most just as
 * efficient but require more development & testing.
 * 
 * bqt::task contains a virtual function matchMask( mask ) that should be used
 * for mask matching rather than getMask() to allow the default algorithm to be
 * overridden by children.  getMask() still exists so that tasks can opt whether
 * to store the mask as a variable or simply return it to save space.  It is
 * pure virtual to force a decision.
 * 
 * To submit tasks from non-C++ code (such as Objective-C for Cocoa), it unfor-
 * tunately seems necessary to write a C wrapper function that should follow
 * the format:
 *      void submit_TaskName_task( ... )
 *      {
 *          bqt::submitTask( new TaskName_task( ... ) );
 *      }
 * with the usual #ifdef __cplusplus/extern "C" guards, of course.  Arguments
 * may be passed to the function in a C-friendly form and be converted as
 * needed.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_taskutil.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class task
    {
    public:
        virtual ~task() {};                                                     // Safety
        
        // TODO: pass a task_mask& instead of task_mask*
        virtual bool execute( task_mask* caller_mask ) = 0;                     // Returns true on success, false to re-queue
        
        virtual task_priority getPriority()
        {
            return PRIORITY_NONE;
        }
        
        virtual task_mask getMask() = 0;
        
        virtual bool matchMask( task_mask m )                                   // Supplies the default matching algorithm
        {
            return !( ~m & getMask() );                                         // See bqt_taskutil.h
        }
    };
}

/******************************************************************************//******************************************************************************/

#endif


