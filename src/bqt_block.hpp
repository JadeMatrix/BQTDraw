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

// R = 1 - ( C * ( 1 - K ) + K )
// G = 1 - ( M * ( 1 - K ) + K )
// B = 1 - ( Y * ( 1 - K ) + K )

// 1 - ( a * ( 1 - b ) + b )
// 1 - a( 1 - b ) - b
// 1 - a + ab - b
// 1 - a + b( a - 1 )
// ( 1 - a ) - b( 1 - a )
// ( 1 - a )( 1 - b )

// V = 1 - K;
// R = K * ( 1 - C );
// G = K * ( 1 - M );
// B = K * ( 1 - Y );

// RGB -> CMYK is not easy, we need to preserve data

namespace bqt
{
    class block : public trackable
    {
    protected:
        class frame
        {
        public:
            GLuint view_comp;
            GLuint* data_comps;
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


