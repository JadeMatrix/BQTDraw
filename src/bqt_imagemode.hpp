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
    enum color_base
    {
        COLOR_RGB,
        COLOR_CMY,
        COLOR_CMYK,
        COLOR_HSL
    };                                                                          // No alpha
    
    struct color
    {
        color_base base;
        // TODO: change to something better:
        double values[ 4 ];                                                     // Must sum to 1.0
    };                                                                          // Each color has its own type so we can mix say CMYK & something else
    
    struct img_mode
    {
        unsigned char channel_count;                                            // >= 1, last channel is always Alpha (which share depth with colors but is
                                                                                // usually binary)
        // TODO: change this too:
        color channel_colors[ 5 ];                                              // Color spec for each channel
        unsigned char depth;                                                    // Depth bit count
        unsigned char dpi;
    };                                                                          // Bytes = ( channels * depth + 7 ) / 8
    
    typedef unsigned char* raw;
    typedef float* pack_space;
    
    raw allocBitmapSpace( img_mode* mode,
                          raw original = NULL );                                // Allocate a 2^exp x 2^exp space as an array, copying original if not NULL
                                                                                // Throws exceptions on bad values & out-of-memory
    
    pack_space allocPackSpace();                                                // Returns a 4 * bsize * sizeof( float ) chunk of memory
    void releasePackSpace( pack_space s );                                      // Releases memory claimed by allocPackSpace()
    void cleanPackSpaces();                                                     // Cleans up memory preallocated to packing; call as part of termination
    
    color convertColor( color source, color_base& from, color_base& to );
    
    raw     convertRawPixels(   raw source,
                                raw target,
                                img_mode& from,
                                img_mode& to );                                 // If target is NULL, allocates target space; target is returned either way
    float*  convertRawPixels_f( raw source,
                                float* target,
                                img_mode& from,
                                img_mode& to );
    double* convertRawPixels_d( raw source,
                                double* target,
                                img_mode& from,
                                img_mode& to );
}

/******************************************************************************//******************************************************************************/

#endif


