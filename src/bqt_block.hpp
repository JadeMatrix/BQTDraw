#ifndef BQT_BLOCK_HPP
#define BQT_BLOCK_HPP

/* 
 * bqt_block.hpp
 * 
 * >> block
 * 
 * UpdateBlock_task pushes an associated PullBlockData_task on creation; this
 * ensures the latter is queued first.  This is done so that texture pulling
 * and block updating can happen on separate threads.  This won't help unless
 * there's more than one block being updated at once; as blocks represent
 * relatively small-sized sections of a canvas, this is a reasonable assump-
 * tion.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_mutex.hpp"
#include "bqt_task.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class block
    {
        friend class UpdateBlock_task;;
    protected:
        struct frame
        {
            unsigned int timestamp;                                             // Timestamp for frame; considered changing to timespec?
            frame* previous;                                                    // Previous frame in undo chain (treated as next in redo)
            unsigned char* data;                                                // Bitmap data, allocated based on parent layer attributes
        };
        
        frame* frames;
        frame* redo_frames;                                                     // Each undone frame is pushed to here; cleared & nullified on edit
        
        unsigned int timestamp;                                                 // Current timestamp for entire block; updated whenever a new update is QUEUED
        
        // layer& parent;
        mutex block_mutex;
        
        void pushBackFrames( unsigned char* data = NULL );                      // Pushes back the frame stack & clears redo data
                                                                                // If data is NULL allocates & copies previous
        void undo();
    public:
        block( /* layer p */ ) /* : parent( p ) */;
        ~block();
    };
    
    class UpdateBlock_task : public task
    {
        friend class PullBlockData_task;
    protected:
        block& target;
        unsigned int timestamp;
        unsigned char* data;                                                    // Initialized to NULL; will request requeue until non-NULL
        mutex ubt_mutex;
    public:
        UpdateBlock_task( block b ) : target( b );                              // Pushes a PullBlockData_task
        
        bool execute( task_mask* caller_mask );                                 // Will return false until data is non-NULL or block timestamp is newer
        
        // PRIORITY_NONE
        
        task_mask getMask()
        {
            return TASK_ALL;
        }
    };
    
    class PullBlockData_task : public task                                      // Pulls block texture data from the GPU
    {
    protected:
        UpdateBlock_task& counterpart;
    public:
        PullBlockData_task( UpdateBlock_task ubt ) : counterpart( ubt );
        
        bool execute( task_mask* caller_mask );                                 // Pulls texture from GPU, formats, and fills data in counterpart
        
        // PRIORITY_NONE
        
        task_mask getMask()
        {
            return TASK_GPU;
        }
    };
}

/******************************************************************************//******************************************************************************/

#endif


