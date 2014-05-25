#ifndef BQT_SLICE_HPP
#define BQT_SLICE_HPP

/* 
 * bqt_slice.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_frame.hpp"
#include "bqt_timestamp.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class slice
    {
    protected:
        frame* stack;
        frame* redo_stack;
        timestamp stamp;
    public:
    };
}

/******************************************************************************//******************************************************************************/

#endif


