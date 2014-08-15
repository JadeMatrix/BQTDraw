/* 
 * bqt_preferences.cpp
 * 
 * Implements bqt_preferences.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_preferences.hpp"

#include <cmath>

#include "bqt_imagemode.hpp"
#include "threading/bqt_rwlock.hpp"
#include "bqt_log.hpp"
#include "bqt_exception.hpp"
#include "bqt_launchargs.hpp"

/* DEFAULTS *******************************************************************//******************************************************************************/

#ifdef __APPLE__
#define PREFERENCE_QUITONNOWINDOW   false
#else
#define PREFERENCE_QUITONNOWINDOW   true
#endif
#define PREFERENCE_BLOCKEXPONENT    8
#define PREFERENCE_BLOCKEXP_RMAX    7
#define PREFERENCE_MAXUNDO          -1
#define PREFERENCE_CLICKDISTMM      3.0f

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    bqt::rwlock pref_lock;
    
    bool          quit_on_no_windows;
    unsigned char block_exponent;
    long          max_undo_steps;
    float         click_dist_mm;
}

/******************************************************************************//******************************************************************************/

namespace bqt
{
    void loadPreferencesFile( std::string f )
    {
        scoped_lock< rwlock > slock( pref_lock, RW_WRITE );
        
        resetPreferencesToDefaults();
        
        ff::write( bqt_out, "Preference file loading not implemented, skipping\n" );    // TODO: implement
    }
    void resetPreferencesToDefaults()
    {
        scoped_lock< rwlock > slock( pref_lock, RW_WRITE );
        
        if( getDevMode() )
            ff::write( bqt_out, "Setting preferences to defaults\n" );
        
        quit_on_no_windows = PREFERENCE_QUITONNOWINDOW;
        block_exponent     = PREFERENCE_BLOCKEXPONENT;
        max_undo_steps     = PREFERENCE_MAXUNDO;
        click_dist_mm      = PREFERENCE_CLICKDISTMM;
    }
    
    // Quit on no windows //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    bool tryQuitOnNoWindows()
    {
    #ifdef __APPLE__                                                            // TODO: Detect all platforms where this is available
        return true;
    #else
        return false;
    #endif
    }
    bool getQuitOnNoWindows()
    {
        scoped_lock< rwlock > slock( pref_lock );
        
        return quit_on_no_windows;
    }
    void setQuitOnNoWindows( bool s )
    {
        scoped_lock< rwlock > slock( pref_lock, RW_WRITE );
        
        if( tryQuitOnNoWindows() )
            quit_on_no_windows = s;
        else
        {
            ff::write( bqt_out, "Warning: BQTDraw will always exit with no windows open on this platform, ignoring\n" );
            quit_on_no_windows = true;
        }
    }
    
    // Block exponent //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    bool tryBlockExponent()
    {
        #warning tryBlockExponent() does not check if a file is open
        // TODO: if a file is open return false, otherwise return true
        return true;
    }
    unsigned char getBlockExponent()
    {
        scoped_lock< rwlock > slock( pref_lock );
        
        return block_exponent;
    }
    void setBlockExponent( unsigned char e )
    {
        scoped_lock< rwlock > slock( pref_lock, RW_WRITE );
        
        if( e < BLOCKEXPONENT_MIN || e > BLOCKEXPONENT_MAX )
            throw exception( "Block size exponent must be between " MACROTOSTR( BLOCKEXPONENT_MIN ) " and " MACROTOSTR( BLOCKEXPONENT_MAX ) );
        
        if( tryBlockExponent() )
        {
            block_exponent = e;
            
            if( block_exponent < PREFERENCE_BLOCKEXP_RMAX )
                ff::write( bqt_out, "Warning: block exponent below recommended minimum (", PREFERENCE_BLOCKEXP_RMAX, ")\n" );
            
            if( getDevMode() )
            {
                long block_w = pow( 2, block_exponent );
                ff::write( bqt_out, "Block size set to ", block_w, " x ", block_w, "\n" );
            }
        }
        else
            ff::write( bqt_out, "Could not set block exponent size\n" );
    }
    
    // Undo/redo steps /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    bool tryMaxUndoSteps()
    {
        return true;
    }
    long getMaxUndoSteps()
    {
        scoped_lock< rwlock > slock( pref_lock );
        
        return max_undo_steps;
    }
    void setMaxUndoSteps( long s )
    {
        scoped_lock< rwlock > slock( pref_lock, RW_WRITE );
        
        if( s < -1 )
            throw exception( "Max undo/redo steps must be -1 or greater" );
        
        if( tryMaxUndoSteps() )
        {
            max_undo_steps = s;
            
            if( getDevMode() )
            {
                if( max_undo_steps < 0 )
                    ff::write( bqt_out, "Max undo/redo steps not limited\n" );
                else
                    ff::write( bqt_out, "Max undo/redo limited to ", max_undo_steps, " steps\n" );
            }
        }
        else
            ff::write( bqt_out, "Could not set max undo/redo steps\n" );
    }
    
    // Click distance //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    bool tryClickDistance()
    {
        return true;
    }
    float getClickDistance()
    {
        scoped_lock< rwlock > slock( pref_lock );
        
        return click_dist_mm;
    }
    void setClickDistance( float d )
    {
        scoped_lock< rwlock > slock( pref_lock, RW_WRITE );
        
        if( tryClickDistance() )
            click_dist_mm = d;
        else
            ff::write( bqt_out, "Could not set click distance\n" );
    }
}


