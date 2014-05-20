#ifndef BQT_LAYER_HPP
#define BQT_LAYER_HPP

/* 
 * bqt_layer.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_imagemode.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class layer
    {
    protected:
        img_mode mode;
    public:
        layer();
        ~layer();
        
        img_mode* getMode()
        {
            return &mode;
        }
    };
}

/******************************************************************************//******************************************************************************/

#endif


