#ifndef BQT_FRAME_HPP
#define BQT_FRAME_HPP

/* 
 * bqt_frame.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_gl.hpp"
#include "bqt_timestamp.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class frame
    {
    protected:
        GLuint comp;
        timestamp stamp;
        frame* previous
        unsigned char* data;                                                    // Bitmap data, allocated based on parent layer attributes
    public:
        frame( img_mode* mode );                                                // Constructors always set timestamp to 0
        frame( img_mode* mode, frame* previous );
        frame( img_mode* mode, unsigned char* data );                           // Only used for first frame
        ~frame();
    };
}

/******************************************************************************//******************************************************************************/

#endif


