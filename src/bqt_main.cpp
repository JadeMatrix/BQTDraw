/* 
 * bqt_main.cpp
 * 
 * Core program initialization
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <iostream>

#include "bqt_launchargs.hpp"

/******************************************************************************//******************************************************************************/

int main( int argc, char* argv[] )
{
    int exit_code = 0x00;
    
    try
    {
        bqt::parseLaunchArgs( argc, argv );
    }
    catch( std::exception& e )
    {
        std::cout << e.what();
        
        exit_code = 0x01;
    }
    
    return exit_code;
}


