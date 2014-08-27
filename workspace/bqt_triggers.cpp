/* 
 * bqt_triggers.cpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_triggers.hpp"

#ifdef PLATFORM_XWS_GNUPOSIX
#include <sys/select.h>                                                         // Synchronous I/O multiplexing 
#include <sys/time.h>
#endif

#include "bqt_platform.h"
#include "threading/bqt_thread.hpp"
#include "threading/bqt_mutex.hpp"
#include "bqt_events.hpp"
#include "bqt_log.hpp"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    bqt::mutex trigger_mutex;
    bool trigger_loop_running = false;
    
    bqt::exit_code triggerLoop( void* data )
    {
        #ifdef PLATFORM_XWS_GNUPOSIX
        
        Display* x_display = getXDisplay();
        
        int x_fd = ConnectionNumber( x_display );
        fd_set x_infds;
        
        timeval timeout;
        
        #endif
        
        while( true )
        {
            {
                // bqt::scoped_lock< bqt::mutex > slock( trigger_mutex );
                
                trigger_mutex.lock();
                if( !trigger_loop_running )
                {
                    trigger_mutex.unlock();
                    return bqt::EXITCODE_FINE;
                }
                trigger_mutex.unlock();
            }
            
            #ifdef PLATFORM_XWS_GNUPOSIX
            
            XFlush( x_display );
            
            FD_ZERO( &x_infds );
            FD_SET( x_fd, &x_infds );
            
            timeout.tv_usec = 0;
            timeout.tv_sec  = 1;                                                // Need to reset this, as select() will change it
            
            // if( !getQuitFlag() )
                select( x_fd + 1, &x_infds, 0, 0, &timeout );
            // else
            //     ff::write( bqt_out, "Timeout on trigger loop\n" );
            
            bqt::handleEvents();
            
            // bqt::submitHandleEventsTask();
            
            
            // if( select( x_fd + 1, &x_infds, 0, 0, &timeout ) )
            // {
                
                
            //     bqt::submitHandleEventsTask();
                
                
            // }
            
            // if( getQuitFlag() )
            //     return bqt::EXITCODE_FINE;
            
            
            #else
            
            #warning bqt_triggers.cpp compiled with no trigger loop (not implemented on this platform)
            #define DISABLE_TRIGGER_LOOP
            
            #endif
        }
        
        return bqt::EXITCODE_FINE;
    }
    
    bqt::thread trigger_thread( triggerLoop, NULL );
}

/******************************************************************************//******************************************************************************/

namespace bqt
{
    void initTriggers()
    {
        #ifdef DISABLE_TRIGGER_LOOP                                             // Just a little safety, you won't get events but you won't lock up either
        trigger_loop_running = false;
        #else
        trigger_loop_running = true;
        #endif
        
        trigger_thread.start();
    }
    void deInitTriggers()
    {
        // ff::write( bqt_out, "Attempting deInitTriggers()...\n" );
        
        if( trigger_loop_running )                                              // Only if it was initialized
        {
            {
                // scoped_lock< bqt::mutex > slock( trigger_mutex );
                trigger_mutex.lock();
                trigger_loop_running = false;
                trigger_mutex.unlock();
            }
            
            // ff::write( bqt_out, "Wating for trigger thread\n" );
            
            ff::write( bqt_out,
                       "Trigger thread exited with code ",
                       exc2str( trigger_thread.wait() ),
                       "\n" );
        }
    }
}


