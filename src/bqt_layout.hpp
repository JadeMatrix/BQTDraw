#ifndef BQT_LAYOUT_HPP
#define BQT_LAYOUT_HPP

/* 
 * bqt_layout.hpp
 * 
 * Inside-window layout handling
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <vector>

#include "bqt_canvas.hpp"
#include "bqt_windowevent.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class canvas_layout
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
        canvas_layout();
        
        void acceptEvent( window_event& e );
        
        void draw();
    };
    
    class gui_layout
    {
    protected:
        canvas_layout canvasses;
    public:
        void acceptEvent( window_event& e );
        
        void draw();
    };
}

/******************************************************************************//******************************************************************************/

#endif


