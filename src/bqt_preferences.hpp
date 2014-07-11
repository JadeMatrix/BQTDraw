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
    
    bool tryQuitOnNoWindow();
    bool getQuitOnNoWindows();
    void setQuitOnNoWindows( bool s );
}

/******************************************************************************//******************************************************************************/

#endif


