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
    };
    
    class block_texture
    {
    public:
        GLuint comp;                                                            // Composite texture, includes mipmaps
        GLuint* chan_texs;                                                      // Array of individual textures, may combine channels into single texture(s)
        img_mode* mode;                                                         // Mode for the block
        
        block_texture( img_mode* mode )
        {
            comp = 0;
            chan_texs = NULL;
            this -> mode = mode;
        }
    };
    
    unsigned char* allocBitmapSpace( img_mode* mode,
                                     unsigned char exponent,
                                     unsigned char* original = NULL );          // Allocate a 2^exp x 2^exp space as an array, copying original if not NULL
    
    unsigned char* unpackBitmapFromGPU( block_texture* channel_texture,
                                        unsigned char* data = NULL );           // Unpacks textures and returns them in mode; if data is not NULL writes there
    block_texture*     packBitmapToGPU( block_texture* channel_texture,
                                        unsigned char* data );                  // Packs data in mode into texture(s); if channel_textures is filled out those
                                                                                // textures are used; otherwise new textures are generated; returns the array
                                                                                // of texture ids.  channel_texture contains the mode.
}

/******************************************************************************//******************************************************************************/

#endif


