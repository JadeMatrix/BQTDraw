#ifndef BQT_LAYOUT_HPP
#define BQT_LAYOUT_HPP

/* 
 * bqt_layout.hpp
 * 
 * GUI layout handling
 * 
 * Even though GUIs are by definition locked to a window, layout and
 * layout_element are thread-safe for any future needs.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <vector>
#include <map>

#include "bqt_canvas.hpp"
#include "bqt_windowevent.hpp"
#include "bqt_mutex.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class layout_element
    {
    protected:
        mutex element_mutex;
        
        int position[ 2 ];
        unsigned int dimensions[ 2 ];
        
        bool event_fallthrough;                                                 // Allow events to fall through if not accepted; true by default
    public:
        layout_element( int x,
                        int y,
                        unsigned int w,
                        unsigned int h );
        
        std::pair< unsigned int, unsigned int > getDimensions();
        void setDimensions( unsigned int w, unsigned int h );
        
        std::pair< int, int > getPosition();
        void setPosition( int x, int y );
        
        bool getEventFallthrough();
        void setEventFallthrough( bool f );
        
        virtual layout_element* acceptEvent( window_event&e ) = 0;              // If the event was accepted, returns a pointer to the layout_element that
                                                                                // accepted, else returns NULL.  If event_fallthrough is false should always
                                                                                // returns a pointer to a layout_element, even it it's this.
        
        virtual void draw() = 0;
    };
    
    class layout
    {
    protected:
        mutex layout_mutex;
        
        unsigned int dimensions[ 2 ];
        
        std::vector< layout_element* > elements;
        
        std::map< bqt_platform_idevid_t, layout_element* > input_assoc;
    public:
        layout( unsigned int w, unsigned int h );
        
        std::pair< unsigned int, unsigned int > getDimensions();
        void setDimensions( unsigned int w, unsigned int h );
        
        void acceptEvent( window_event& e );
        
        void draw();
    };
}

/******************************************************************************//******************************************************************************/

#endif


