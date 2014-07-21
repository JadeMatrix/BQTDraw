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

#if 0

void block::frame::packToGPU()
{
    unsigned long mask = exp( 2, mode.depth ) - 1;
    
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
    float alpha = 0.0f;
    
    switch( mode.channels )
    {
    case 0:
        throw exception( "block::frame::packToGPU(): Image mode channels cannot be 0" );
        break;
    case 1:         // B&W (alpha)
        
        break;
    case 4:         // 
        
        break;
    case 5:         // 
        
        break;
    default:
        ff::write( bqt_out, "Channel counts other than 1,4,5 not implemented yet\n" );
        break;
    }
}

#endif

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


