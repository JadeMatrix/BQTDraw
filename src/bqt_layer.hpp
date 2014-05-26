#ifndef BQT_LAYER_HPP
#define BQT_LAYER_HPP

/* 
 * bqt_layer.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_datastructures.hpp"

#include "bqt_slice.hpp"
#include "bqt_imagemode.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class layer
    {
    protected:
        long width;                                                    // In pixels
        long height;
        slice* slices;
        img_mode mode;
    public:
        layer( img_mode& m, long w, long h /*, file_layer*? fl = NULL */ );
        ~layer();
        
        img_mode* getMode()
        {
            return &mode;
        }
    };
}

/******************************************************************************//******************************************************************************/

#endif


