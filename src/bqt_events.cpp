/* 
 * bqt_events.cpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_events.hpp"

#include <SDL2/SDL_events.h>
#include "bqt_taskexec.hpp"
#include "bqt_windowmanagement.hpp"

#include "bqt_log.hpp"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    
}

/******************************************************************************//******************************************************************************/

namespace bqt
{
    bool HandleEvents_task::execute( task_mask* caller_mask )
    {
        {
            SDL_Event sdl_event;
            
            while( SDL_PollEvent( &sdl_event ) )                                // Ugh, unsafe: not guaranteed to terminate
            {
                switch( sdl_event.type )
                {
                case SDL_DOLLARGESTURE:
                    break;
                case SDL_DROPFILE:
                    break;
                case SDL_FINGERMOTION:
                    break;
                case SDL_FINGERDOWN:
                    break;
                case SDL_FINGERUP:
                    break;
                case SDL_KEYDOWN:
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_JOYAXISMOTION:
                    break;
                case SDL_JOYBALLMOTION:
                    break;
                case SDL_JOYHATMOTION:
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                case SDL_JOYBUTTONUP:
                    break;
                case SDL_MOUSEMOTION:
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
                case SDL_MOUSEWHEEL:
                    break;
                case SDL_MULTIGESTURE:
                    break;
                case SDL_QUIT:
                    {
                        ff::write( bqt_out, "Got quit event\n" );
                        closeAllWindows();
                        submitTask( new StopTaskSystem_task() );
                    }
                    break;
                case SDL_SYSWMEVENT:
                    break;
                case SDL_TEXTEDITING:
                    break;
                case SDL_TEXTINPUT:
                    break;
                case SDL_USEREVENT:
                    break;
                case SDL_WINDOWEVENT:
                    {
                        switch( sdl_event.window.event )
                        {
                            case SDL_WINDOWEVENT_SHOWN:
                                
                                break;
                            case SDL_WINDOWEVENT_HIDDEN:
                                
                                break;
                            case SDL_WINDOWEVENT_EXPOSED:
                                
                                break;
                            case SDL_WINDOWEVENT_MOVED:
                                
                                break;
                            case SDL_WINDOWEVENT_RESIZED:
                                
                                break;
                            case SDL_WINDOWEVENT_SIZE_CHANGED:
                                
                                break;
                            case SDL_WINDOWEVENT_MINIMIZED:
                                
                                break;
                            case SDL_WINDOWEVENT_MAXIMIZED:
                                
                                break;
                            case SDL_WINDOWEVENT_RESTORED:
                                
                                break;
                            case SDL_WINDOWEVENT_ENTER:
                                
                                break;
                            case SDL_WINDOWEVENT_LEAVE:
                                
                                break;
                            case SDL_WINDOWEVENT_FOCUS_GAINED:
                                
                                break;
                            case SDL_WINDOWEVENT_FOCUS_LOST:
                                
                                break;
                            case SDL_WINDOWEVENT_CLOSE:
                                
                                break;
                        }
                    }
                    break;
                default:
                    NULL;
                }
            }
        }
        
        return false;                                                           // Requeue instead of submitting a new copy
    }
}


