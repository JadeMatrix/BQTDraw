/* 
 * bqt_threadutil.cpp
 * 
 * Implements bqt_threadutil.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_threadutil.hpp"

#include <unistd.h>

/******************************************************************************//******************************************************************************/

namespace bqt
{
    long getSystemCoreCount()
    {
        return sysconf( _SC_NPROCESSORS_ONLN );
    }
}


