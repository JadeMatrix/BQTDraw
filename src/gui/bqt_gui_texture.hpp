#ifndef BQT_GUI_TEXTURE_HPP
#define BQT_GUI_TEXTURE_HPP

/* 
 * bqt_gui_texture.hpp
 * 
 * Simple wrapper for OpenGL textures
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "../bqt_gl.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    struct gui_texture
    {
        GLuint gl_texture;
        unsigned int dimensions[ 2 ];
        
        gui_texture()
        {
            gl_texture = 0x00;
            
            dimensions[ 0 ] = 0;
            dimensions[ 1 ] = 0;
        }
    };
    
    gui_texture* acquireTexture( std::string filename );
    void releaseTexture( gui_texture* t );
}

/******************************************************************************//******************************************************************************/

#endif


