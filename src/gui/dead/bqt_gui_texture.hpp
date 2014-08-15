#ifndef BQT_GUI_TEXTURE_HPP
#define BQT_GUI_TEXTURE_HPP

/* 
 * bqt_gui_texture.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "../bqt_gl.hpp"
#include "../bqt_png.hpp"
#include "../bqt_mutex.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    struct gui_texture
    {
        GLuint gl_texture;
        unsigned int dimensions[ 2 ];
        
        gui_texture();
    };
}

/******************************************************************************//******************************************************************************/

#endif

