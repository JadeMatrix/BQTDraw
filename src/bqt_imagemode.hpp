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
    };
    
    unsigned char* allocBitmapSpace( img_mode* mode,
                                     unsigned char exponent,
                                     unsigned char* original = NULL );          // Allocate a 2^exp x 2^exp space as an array, copying original if not NULL
    
    unsigned char* unpackBitmapFromGPU( img_mode* mode,
                                        GLuint* channel_textures,
                                        unsigned char* data = NULL );           // Unpacks textures and returns them in mode; if data is not NULL writes there
    GLuint*            packBitmapToGPU( img_mode* mode,
                                        GLuint* channel_textures,
                                        unsigned char* data );                  // Packs data in mode into texture(s); if channel_textures is not NULL those
                                                                                // textures are used; otherwise new textures are generated; returns the array
                                                                                // of texture ids.
}

/******************************************************************************//******************************************************************************/

#endif


