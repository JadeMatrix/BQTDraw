#ifndef BQT_LAYOUT_HPP
#define BQT_LAYOUT_HPP

/* 
 * bqt_layout.hpp
 * 
 * GUI layout handling
 * 
 * Even though GUIs are by definition locked to a window, layout is thread-safe
 * for any future needs.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <vector>
#include <map>

#include "bqt_windowevent.hpp"
#include "bqt_mutex.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class layout_element;                                                       // Defined int gui/bqt_layout_element.hpp
    
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
        
        void associateDevice( bqt_platform_idevid_t dev_id,
                              layout_element* element );                        // Begins sending input events from the device directly to the element without
                                                                                // passing through the element tree; deassociates if element is NULL.
        
        void acceptEvent( window_event& e );
        
        void draw();
    };
}

/******************************************************************************//******************************************************************************/

#endif


