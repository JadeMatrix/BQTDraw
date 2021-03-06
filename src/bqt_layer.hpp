#ifndef BQT_LAYER_HPP
#define BQT_LAYER_HPP

/* 
 * bqt_sketch.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_datastructures.hpp"

#include <vector>

#include "bqt_slice.hpp"
#include "bqt_imagemode.hpp"
#include "bqt_trackable.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class layer
    {
    protected:
        long docpos_x;
        long docpos_y;
        long width;
        long height;
        unsigned int DPI;
    public:
    };
}

/******************************************************************************//******************************************************************************/

#endif


