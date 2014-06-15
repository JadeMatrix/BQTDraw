#ifndef BQT_SLICE_HPP
#define BQT_SLICE_HPP

/* 
 * bqt_slice.hpp
 * 
 * slices do not store their own position
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_datastructures.hpp"

#include <vector>

#include "bqt_block.hpp"
#include "bqt_timestamp.hpp"
#include "bqt_imagemode.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class slice
    {
    protected:
        struct subslice
        {
            block* source;
            float x_off;                                                        // As a fraction of slice widths
            float y_off;                                                        // As a fraction of slice heights
        };
        
        std::vector< subslice > subslices;
        
        GLuint comp;                                                            // Comp is updated whenever zoom increases enough (~2x)
        float zoom;
    public:
        void draw( float zoom );                                                // Pass the current zoom so we know when it changes
    };
}

/******************************************************************************//******************************************************************************/

#endif


