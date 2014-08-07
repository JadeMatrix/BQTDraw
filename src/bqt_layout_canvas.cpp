/* 
 * bqt_layout_canvas.cpp
 * 
 * Implements bqt_layout_canvas.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_layout_canvas.hpp"
 
#include "bqt_gl.hpp"
#include "bqt_exception.hpp"

/******************************************************************************//******************************************************************************/

// void drawCircle( unsigned int sides, float radius = 1.0, bool fill = true )
// {
//     ff::write( bqt_out, "Drawing a circle\n" );
    
//     if( fill )
//         glBegin( GL_POLYGON );
//     else
//         glBegin( GL_LINE_LOOP );
//     {
//         glPushMatrix();
//         {
//             // glTranslatef( radius, 0.0, 0.0 );
            
//             for( int i = 0; i < sides; i++ )
//             {
//                 glRotatef( 360.0f / sides, 1.0, 0.0, 0.0 );
                
//                 glVertex2f( radius, 0.0 );
//             }
//         }
//         glPopMatrix();
//     }
//     glEnd();
// }

/******************************************************************************//******************************************************************************/

namespace bqt
{
    canvas_element::canvas_element( int x,
                                    int y,
                                    unsigned int w,
                                    unsigned int h ) : layout_element( x, y, w, h )
    {
        root.type = pane::EMPTY;
        root.contents = NULL;
    }
    
    layout_element* canvas_element::acceptEvent( window_event& e )
    {
        scoped_lock slock( element_mutex );
        
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
        
        return NULL;
    }
    
    void canvas_element::draw()
    {
        
    }
}


