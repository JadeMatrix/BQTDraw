/* 
 * bqt_layout.cpp
 * 
 * Implements layout handlers from bqt_layout.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_layout.hpp"

#include "bqt_exception.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    /* CANVAS_LAYOUT **********************************************************//******************************************************************************/
    
    canvas_layout::canvas_layout()
    {
        root.type = pane::EMPTY;
        root.contents = NULL;
    }
    
    void canvas_layout::acceptEvent( window_event& e )
    {
        switch( e.type )
        {
        case STROKE:
            break;
        case DROP:
            break;
        case KEYCOMMAND:
            break;
        case COMMAND:
            break;
        case TEXT:
            break;
        default:
            throw exception( "canvas_layout::acceptEvent(): Uknown event type" );
            break;
        }
    }
    
    void canvas_layout::draw()
    {
        
    }
    
    /* GUI_LAYOUT *************************************************************//******************************************************************************/
    
    void gui_layout::acceptEvent( window_event& e )
    {
        switch( e.type )
        {
        case STROKE:
            if( true )                                                          // Within some gui element
                break;
            else
                canvasses.acceptEvent( e );                                     // Pass to the canvas layout
        case DROP:
            if( true )
                break;
            else
                canvasses.acceptEvent( e );
        case KEYCOMMAND:
            if( true )
                break;
            else
                canvasses.acceptEvent( e );
        case COMMAND:
            if( true )
                break;
            else
                canvasses.acceptEvent( e );
        case TEXT:
            if( true )
                break;
            else
                canvasses.acceptEvent( e );
        default:
            throw exception( "gui_layout::acceptEvent(): Uknown event type" );
            break;
        }
    }
    
    void gui_layout::draw()
    {
        
        
        canvasses.draw();
    }
}


