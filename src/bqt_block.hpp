#ifndef BQT_BLOCK_HPP
#define BQT_BLOCK_HPP

/* 
 * bqt_block.hpp
 * 
 * Contains bqt::block for storing layer block data in RAM, as well as various
 * utility tasks.
 * 
 * UpdateBlock_task pushes an associated PullBlockData_task on creation; this
 * ensures the latter is queued first.  This is done so that texture pulling
 * and block updating can happen on separate threads.  This won't help unless
 * there's more than one block being updated at once; as blocks represent
 * relatively small-sized sections of a canvas, this is a reasonable assump-
 * tion.
 * 
 * BQTDraw uses a GPU-masked task thread rather than GPU locks.  While calling
 * OpenGL from multiple threads using a lockable context may work, it is not
 * well-documented (probably as concurrent OpenGL is rightfully discouraged for
 * most common applications of hardware acceleration) and so may not be entirely
 * cross-platform.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_mutex.hpp"
#include "bqt_task.hpp"
#include "bqt_timestamp.hpp"
#include "bqt_imagemode.hpp"
#include "bqt_layer.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class block
    {
        friend class UpdateBlock_task;
        friend class UpdateBlockTexture_task;
        friend class PullBlockData_task;
    protected:
        class frame                                                             // Class so we get RAII benefits
        {
        protected:
            void init( img_mode* mode, frame* previous );
        public:
            timestamp stamp;                                                    // Timestamp for frame (value implementation-defined)
            frame* previous;                                                    // Previous frame in undo chain (treated as next in redo)
            img_mode* mode;                                                     // Image mode for data, linked from the parent layer (does not change)
            unsigned char* data;                                                // Bitmap data, allocated based on parent layer attributes
            
            frame( img_mode* mode );                                            // Constructors always set timestamp to 0
            frame( img_mode* mode, frame* previous );
            frame( img_mode* mode, unsigned char* data );                       // Only used for first frame
            ~frame();
        };
        
        frame* frames;
        frame* redo_frames;                                                     // Each undone frame is pushed to here; cleared & nullified on edit
        
        GLuint* channel_textures;
        
        timestamp stamp;                                                        // Current timestamp for entire block; updated whenever a new update is QUEUED
        
        layer& parent;
        mutex block_mutex;
        
        void pushBackFrames( timestamp stamp );                                 // Sets top frame's stamp, pushes back the frame stack & clears redo data
        
        void shiftFrame( frame*& from, frame*& to );                            // Utility function for undo/redo
        bool undo();
        bool redo();
        
        frame* getFrameFromTimestamp( timestamp stamp );                        // Not thread-safe, assumes block_mutex has already been locked
    public:
        block( layer& p, unsigned char* data );
        ~block();
    };
    
    class UpdateBlock_task : public task
    {
        friend class PullBlockData_task;
    protected:
        block& target;
        unsigned char* data;                                                    // Initialized to NULL; will request requeue until non-NULL
        timestamp stamp;                                                        // Timestamp of the frame to update
        mutex ubt_mutex;
    public:
        UpdateBlock_task( block& b, timestamp stamp );                          // Pushes a PullBlockData_task
                                                                                // Pass the timestamp too to make it easier to ensure it's correct
        
        bool execute( task_mask* caller_mask );                                 // Will return false until data is non-NULL
        
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
        PullBlockData_task( UpdateBlock_task& ubt );
        
        bool execute( task_mask* caller_mask );                                 // Pulls texture from GPU, formats, and fills data in counterpart
        
        task_priority getPriority()
        {
            return PRIORITY_HIGH;                                               // Needs to be on the same priority level as drawing so we don't loose data
        }
        
        task_mask getMask()
        {
            return TASK_GPU;
        }
    };
    
    class UpdateBlockTexture_task : public task
    {
    protected:
        block& source;
        timestamp stamp;
    public:
        UpdateBlockTexture_task( block& b, timestamp stamp );                   // Pass the timestamp too to make it easier to ensure it's correct
        
        bool execute( task_mask* caller_mask );                                 // Will simply exit if timestamp is older than block's timestamp
        
        // PRIORITY_NONE
        
        task_mask getMask()
        {
            return TASK_GPU;
        }
    };
}

/******************************************************************************//******************************************************************************/

#endif


