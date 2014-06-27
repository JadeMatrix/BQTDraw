#ifndef BQT_BLOCK_HPP
#define BQT_BLOCK_HPP

/* 
 * bqt_block.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_datastructures.hpp"

#include "bqt_gl.hpp"
#include "bqt_sketch.hpp"
#include "bqt_trackable.hpp"
#include "bqt_imagemode.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class block : public trackable
    {
    protected:
        class frame
        {
        public:
            GLuint* comps;                                                      // Array of [1] for now (RGBA), to be expanded to channel mixes later
            raw data;
            image_mode& mode;
            
            frame( img_mode& m, raw data = NULL );
            ~frame();
            
            void packToGPU();
            void unpackFromGPU();
        };
        
        frame* undo_stack;
        frame* redo_stack;
        sketch& parent_sketch;
    public:
        block( sketch& s );
        ~block();
        
        sketch& getSketch();
        
        int undo();
        int redo();
        int undo( timestamp stamp );
        int redo( timestamp stamp );
    };
}

/******************************************************************************//******************************************************************************/

#endif


