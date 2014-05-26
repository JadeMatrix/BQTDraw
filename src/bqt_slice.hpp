#ifndef BQT_SLICE_HPP
#define BQT_SLICE_HPP

/* 
 * bqt_slice.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_datastructures.hpp"

#include <deque>

#include "bqt_frame.hpp"
#include "bqt_timestamp.hpp"
#include "bqt_trackable.hpp"
#include "bqt_imagemode.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class slice : public trackable
    {
    protected:
        std::deque< frame* > undo_stack;                                        // First (back) is current
        std::deque< frame* > redo_stack;
        timestamp stamp;
    public:
        slice( layer& pl, block& pb, unsigned char* data = NULL );              // If data null, allocates all 0's based on the layer's mode
        
        int undo();
        int redo();
        int undo( timestamp stamp );
        int redo( timestamp stamp );
    };
}

/******************************************************************************//******************************************************************************/

#endif


