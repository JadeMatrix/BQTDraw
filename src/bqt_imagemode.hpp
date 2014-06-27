#ifndef BQT_IMAGEMODE_HPP
#define BQT_IMAGEMODE_HPP

/* 
 * bqt_imagemode.hpp
 * 
 * Defines the img_mode struct for storing mode data (channels, depth, etc.) as
 * well as utility functions for converting between internal & OpenGL formats.
 * 
 * Packing/unpacking never return NULL; instead they throw exceptions.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_gl.hpp"

#include <cstddef>

/******************************************************************************//******************************************************************************/

#define BLOCKEXPONENT_MIN   1
#define BLOCKEXPONENT_MAX   255

namespace bqt
{
    struct img_mode
    {
        unsigned char channels;                                                 // >= 1, last channel is always Alpha
        unsigned char depth;                                                    // Depth bit count
        unsigned char dpi;
    };                                                                          // Bytes = ( channels * depth + 7 ) / 8
    
    typedef unsigned char* raw;
    typedef float* pack_space;
    
    raw allocBitmapSpace( img_mode* mode,
                          unsigned char exponent,
                          raw original = NULL );                                // Allocate a 2^exp x 2^exp space as an array, copying original if not NULL
    
    pack_space allocPackSpace();                                                // Returns a 4 * bsize * sizeof( float ) chunk of memory
    void releasePackSpace( pack_space s );                                      // Releases memory claimed by allocPackSpace()
    void cleanPackSpaces();                                                     // Cleans up memory preallocated to packing; call as part of termination
}

/******************************************************************************//******************************************************************************/

#endif


