/* 
 * AppDelegate.m
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#import "AppDelegate.h"

#import "bqt_main.h"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

@implementation AppDelegate
 
- ( void )applicationDidFinishLaunching:( NSNotification* )aNotification
{
    bqt_main();
}

// - ( BOOL )applicationShouldTerminateAfterLastWindowClosed:( NSApplication* )theApplication
// {
//     return NO;
// }

@end


