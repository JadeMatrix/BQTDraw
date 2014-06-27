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
    
    // class block_texture
    // {
    // public:
    //     GLuint comps*;                                                          // Composite textures, includes mipmaps - first is RGBA
    //     raw data;                                                               // Raw pixel data in mode
    //     img_mode& mode;                                                         // Mode for the block
        
    //     block_texture( img_mode* m, raw d = NULL ) : mode( m )
    //     {
    //         comp = 0;
    //         this -> data = d;
    //     }
        
    //     void unpackFromGPU();
    //     void packToGPU();
    // };
    
    raw allocBitmapSpace( img_mode* mode,
                          unsigned char exponent,
                          raw original = NULL );                                // Allocate a 2^exp x 2^exp space as an array, copying original if not NULL
    
    // raw        unpackBitmapFromGPU( block_texture* channel_texture,
    //                                 raw data = NULL );                          // Unpacks textures and returns them in mode; if data is not NULL writes there
    // block_texture* packBitmapToGPU( block_texture* channel_texture,
    //                                 raw data );                                 // Packs data in mode into texture(s); if channel_textures is filled out those
    //                                                                             // textures are used; otherwise new textures are generated; returns the array
    //                                                                             // of texture ids.  channel_texture contains the mode.
}

/******************************************************************************//******************************************************************************/

#endif


