#ifndef BQT_CANVAS_HPP
#define BQT_CANVAS_HPP

/* 
 * bqt_canvas.hpp
 * 
 * Class that handles all information about an open BQT file/document, and can
 * be attached to a window.
 * Tracks:
 * layer switching (important - don't be like Photoshop), layer reordering,
 * canvas DPI & size, background color
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_datastructures.hpp"

#include "bqt_trackable.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class canvas : public trackable
    {
    protected:
    public:
        int undo();
        int redo();
        int undo( timestamp stamp );
        int redo( timestamp stamp );
    };
}

/******************************************************************************//******************************************************************************/

#endif


