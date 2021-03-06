/* 
 * unix_bqt_main.cpp
 * 
 * bqt_main() wrapper for UNIX platforms
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_main.h"

/******************************************************************************//******************************************************************************/

int main( int argc, char* argv[] )
{
    if( bqt_parseLaunchArgs( argc, argv ) )
        return bqt_main();
    else
        return 0;
}


