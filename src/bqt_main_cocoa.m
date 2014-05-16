/* 
 * bqt_main.m
 * 
 * Implements main() wrapping on OS X with Cocoa; see AppDelegate.h &
 * AppDelegate.m for more Cocoa wrapping.
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#import <Cocoa/Cocoa.h>

#import "bqt_main.h"

/******************************************************************************//******************************************************************************/

int main( int argc, char* argv[] )
{
    bqt_parseLaunchArgs( argc, argv );
    
    return NSApplicationMain( argc, ( const char** )argv );
}


