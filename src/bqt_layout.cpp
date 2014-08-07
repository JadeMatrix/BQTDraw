/* 
 * bqt_layout.cpp
 * 
 * Implements layout handlers from bqt_layout.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_layout.hpp"

#include "bqt_exception.hpp"
#include "bqt_gl.hpp"
#include "bqt_log.hpp"
#include "bqt_launchargs.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    /* LAYOUT_ELEMENT *********************************************************//******************************************************************************/
    
    layout_element::layout_element( int x,
                                    int y,
                                    unsigned int w,
                                    unsigned int h )
    {
        position[ 0 ] = x;
        position[ 1 ] = y;
        dimensions[ 0 ] = w;
        dimensions[ 1 ] = w;
        
        event_fallthrough = true;
    }
    
    std::pair< unsigned int, unsigned int > layout_element::getDimensions()
    {
        scoped_lock slock( element_mutex );
        
        return std::pair< unsigned int, unsigned int >( dimensions[ 0 ], dimensions[ 1 ] );
    }
    void layout_element::setDimensions( unsigned int w, unsigned int h )
    {
        scoped_lock slock( element_mutex );
        
        dimensions[ 0 ] = w;
        dimensions[ 1 ] = w;
    }
    
    std::pair< int, int > layout_element::getPosition()
    {
        scoped_lock slock( element_mutex );
        
        return std::pair< unsigned int, unsigned int >( position[ 0 ], position[ 1 ] );
    }
    void layout_element::setPosition( int x, int y )
    {
        scoped_lock slock( element_mutex );
        
        position[ 0 ] = x;
        position[ 1 ] = y;
    }
    
    bool layout_element::getEventFallthrough()
    {
        scoped_lock slock( element_mutex );
        
        return event_fallthrough;
    }
    void layout_element::setEventFallthrough( bool f )
    {
        scoped_lock slock( element_mutex );
        
        event_fallthrough = f;
    }
    
    /* LAYOUT *****************************************************************//******************************************************************************/
    
    layout::layout( unsigned int w, unsigned int h )
    {
        dimensions[ 0 ] = w;
        dimensions[ 1 ] = h;
    }
    
    std::pair< unsigned int, unsigned int > layout::getDimensions()
    {
        scoped_lock slock( layout_mutex );
        
        return std::pair< unsigned int, unsigned int >( dimensions[ 0 ], dimensions[ 1 ] );
    }
    void layout::setDimensions( unsigned int w, unsigned int h )
    {
        scoped_lock slock( layout_mutex );
        
        dimensions[ 0 ] = w;
        dimensions[ 1 ] = w;
    }
    
    void layout::acceptEvent( window_event& e )
    {
        bool pass_event = false;
        
        switch( e.type )
        {
        case STROKE:
        case PINCH:
            {
                if( input_assoc.count( e.stroke.dev_id ) )
                {
                    if( ( e.type == STROKE && e.stroke.pressure <= 0.0f )
                        || ( e.type == PINCH && e.pinch.finish ) )              // If lifted, de-associate
                        input_assoc.erase( e.stroke.dev_id );
                    
                    input_assoc[ e.stroke.dev_id ] -> acceptEvent( e );         // This works because elements store their position
                }
                else
                    pass_event = true;
            }
            break;
        case DROP:
        case KEYCOMMAND:
        case COMMAND:
            pass_event = true;
            break;
        case TEXT:
            {
                if( e.text.element == NULL )
                    throw exception( "layout::acceptEvent(): Text input event with no associated element" );
                
                e.text.element -> acceptEvent( e );
            }
            break;
        default:
            throw exception( "layout::acceptEvent(): Uknown event type" );
            break;
        }
        
        if( pass_event )
        {
            layout_element* acceptor = NULL;
            
            for( int i = elements.size() - 1; i >= 0; --i )                     // Iterate backwards as last element is topmost
            {
                float position[ 2 ];
                bool no_position = false;
                
                switch( e.type )
                {
                case STROKE:
                    position[ 0 ] = e.stroke.position[ 0 ];
                    position[ 1 ] = e.stroke.position[ 1 ];
                    break;
                case PINCH:
                    position[ 0 ] = e.pinch.position[ 0 ];
                    position[ 1 ] = e.pinch.position[ 1 ];
                    break;
                case DROP:
                    position[ 0 ] = e.drop.position[ 0 ];
                    position[ 1 ] = e.drop.position[ 1 ];
                    break;
                case KEYCOMMAND:
                case COMMAND:
                    no_position = true;
                    break;
                default:
                    break;                                                      // Any other types should have already been handled above
                }
                
                if( no_position )
                {
                    acceptor = elements[ i ] -> acceptEvent( e );
                    
                    if( acceptor != NULL )                                      // layout_element::acceptEvent() must check fallthrough as layout_elements may
                                                                                // have sub elements.
                        break;
                }
                else
                {
                    std::pair< int, int > element_pos = elements[ i ] -> getPosition();
                    std::pair< unsigned int, unsigned int > element_dim = elements[ i ] -> getDimensions();
                    
                    if(    position[ 0 ] <= element_pos.first
                        && position[ 0 ] >  element_pos.first  + element_dim.first
                        && position[ 1 ] <= element_pos.second
                        && position[ 1 ] >  element_pos.second + element_dim.second )
                    {
                        acceptor = elements[ i ] -> acceptEvent( e );
                        
                        if( acceptor != NULL )
                        {
                            if( ( e.type == STROKE && e.stroke.pressure > 0.0f )// Only track events with pressure (ie not hovering)
                                || ( e.type == PINCH && !e.pinch.finish ) )     // Also, no tracking drop events even though they have position
                                input_assoc[ e.stroke.dev_id ] = acceptor;
                            
                            break;
                        }
                    }
                }
            }
            
            if( acceptor == NULL && getDevMode() )
                ff::write( bqt_out, "Warning: event trickled down but not accepted\n" );
        }
    }
    
    void layout::draw()
    {
        // TODO: Implement setup
        
        for( int i = 0; i < elements.size(); ++i )                              // Iterate forwards as last element is topmost
        {
            glPushMatrix();
            {
                std::pair< int, int > pos = elements[ i ] -> getPosition();
                
                glTranslatef( ( float )pos.first,
                              ( float )pos.second,
                              0.0f );
                
                elements[ i ] -> draw();
            }
            glPopMatrix();
        }
    }
}


