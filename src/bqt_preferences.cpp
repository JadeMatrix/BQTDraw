/* 
 * bqt_preferences.cpp
 * 
 * Implements bqt_preferences.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_preferences.hpp"

#include "bqt_mutex.hpp"
#include "bqt_log.hpp"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    bqt::mutex pref_mutex;
    
    bool quit_on_no_windows;
}

/******************************************************************************//******************************************************************************/

namespace bqt
{
    void loadPreferencesFile( std::string f )
    {
        scoped_lock slock( pref_mutex );
        
        quit_on_no_windows = false;
        
        ff::write( bqt_out, "Preference file loading not implemented, skipping\n" );
    }
    
    bool tryQuitOnNoWindows()
    {
    #ifdef __APPLE__
        return true;
    #else
        return false;
    #endif
    }
    bool getQuitOnNoWindows()
    {
        scoped_lock slock( pref_mutex );
        
        return quit_on_no_windows;
    }
    void setQuitOnNoWindows( bool s )
    {
        scoped_lock slock( pref_mutex );
        
    #ifdef __APPLE__                                                            // TODO: Detect all platforms where this is available
        
        quit_on_no_windows = s;
        
    #else
        
        ff::write( bqt_out, "Warning: BQTDraw will always exit with no windows open on this platform, ignoring\n" );
        quit_on_no_windows = false;
        
    #endif
    }
}


