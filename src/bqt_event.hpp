#ifndef BQT_EVENT_HPP
#define BQT_EVENT_HPP

/* 
 * bqt_event.hpp
 * 
 * Events are for general actions on windows and not on the program as a whole.
 * This means they include clicks, drags, etc. but not file opening, quitting,
 * etc. that affect the program as a whole.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/



/******************************************************************************//******************************************************************************/

namespace bqt
{
    enum event_id
    {
        CLICK,
        DRAG,
        DROP,
        COMMAND,
        TEXT
    };
    
    struct event
    {
        event_id id;
        union
        {
            
        } data;
    };
}

/******************************************************************************//******************************************************************************/

#endif


