#ifndef BQT_LAYOUT_CANVAS_HPP
#define BQT_LAYOUT_CANVAS_HPP

/* 
 * bqt_layout_canvas.hpp
 * 
 * GUI element for displaying canvasses
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_layout.hpp"

#include <vector>

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class canvas_element : public layout_element
    {
    protected:
        struct pane
        {
            enum
            {
                EMPTY,
                CANVAS,
                PANES
            } type;
            std::vector< std::pair< pane, float > > children;                   // Should be empty if contents non-NULL
            canvas* contents;
        };
        
        pane root;
    public:
        canvas_element( int x,
                        int y,
                        unsigned int w,
                        unsigned int h );
        
        layout_element* acceptEvent( window_event& e );
        
        void draw();
    };
    
    
}

/******************************************************************************//******************************************************************************/

#endif


