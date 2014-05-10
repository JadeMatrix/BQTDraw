#ifndef BQT_LOG_HPP
#define BQT_LOG_HPP

/* 
 * bqt_log.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <iostream>

/******************************************************************************//******************************************************************************/

namespace bqt
{
    std::ostream* getLogStream();                                               // Returns the std::ostream being used as a log; std::cout by default
    #define bqt_out *bqt::getLogStream()                                        // Macro so we can get the current out stream like ff::write( bqt_out, "...
    
    void closeLog();                                                            // To be called on exit (in main()) to make sure we've cleaned up logging
}

/******************************************************************************//******************************************************************************/

#endif

