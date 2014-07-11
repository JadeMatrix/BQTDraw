#ifndef BQT_VERSION_HPP
#define BQT_VERSION_HPP

/* 
 * bqt_version.hpp
 * 
 * Version information
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_log.hpp"

/******************************************************************************//******************************************************************************/

#define BQT_VERSION_MAJOR   0
#define BQT_VERSION_MINOR   1
#define BQT_VERSION_PATCH   0

#define BQT_VERSION_STRING_M( maj, min, rev )   "BQTDraw alpha " MACROTOSTR( min )  // Version to use until we're out of alpha/beta
// #define BQT_VERSION_STRING_M( maj, min, rev )   "BQTDraw v" MACROTOSTR( BQT_VERSION_MAJOR ) \
//                                                 "." MACROTOSTR( BQT_VERSION_MINOR ) \
//                                                 "." MACROTOSTR( BQT_VERSION_PATCH )

#define BQT_VERSION_STRING BQT_VERSION_STRING_M( BQT_VERSION_MAJOR, BQT_VERSION_MINOR, BQT_VERSION_PATCH )

/******************************************************************************//******************************************************************************/

#endif


