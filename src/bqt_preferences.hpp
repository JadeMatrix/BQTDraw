#ifndef BQT_PREFERENCES_HPP
#define BQT_PREFERENCES_HPP

/* 
 * bqt_preferences.hpp
 * 
 * Loading, reading & setting users preferences
 * 
 * Each setting comes with three functions:
 *     try - test if the setting is settable
 *     get - get the setting value
 *     set - set the setting value
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <string>

/******************************************************************************//******************************************************************************/

namespace bqt
{
    void loadPreferencesFile( std::string f );
    void resetToDefaults();
    
    bool tryQuitOnNoWindow();
    bool getQuitOnNoWindows();
    void setQuitOnNoWindows( bool s );
    
    bool          tryBlockExponent();
    unsigned char getBlockExponent();                                           // Get the block size exponent: blocks are 2^exp x 2^exp textures
    void          setBlockExponent( unsigned char e );
    
    bool tryMaxUndoSteps();
    long getMaxUndoSteps();                                                     // Get the max number of undos; -1 for unlimited
    void setMaxUndoSteps( long s );
}

/******************************************************************************//******************************************************************************/

#endif


