/* 
 * bqt_threadutil.cpp
 * 
 * Implements bqt_threadutil.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_threadutil.hpp"

#include <unistd.h>
#include <stdint.h>

/******************************************************************************//******************************************************************************/

namespace bqt
{
    long getSystemCoreCount()
    {
        return sysconf( _SC_NPROCESSORS_ONLN );
    }
    
    const char* exc2str( exit_code ec )
    {
        switch( ( intptr_t )ec )                                                // We know for certain that this is not a real pointer
        {
            case EXIT_FINE:
                return "EXIT_FINE";
            case EXIT_INITERR:
                return "EXIT_INITERR";
            case EXIT_BQTERR:
                return "EXIT_BQTERR";
            case EXIT_STDERR:
                return "EXIT_STDERR";
            default:
                return "n/a";
        }
    }
}


