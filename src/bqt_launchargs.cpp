/* 
 * bqt_launchargs.cpp
 * 
 * Implements bqt_launchargs.hpp & holds launch arguments state
 * Using the getopt family http://linux.die.net/man/3/getopt
 * 
 * Note that no thread-safety is necessary as launch flags/arguments are set up
 * at launch and do not change.
 * 
 * Also implements bqt_log.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <getopt.h>

#include "bqt_launchargs.hpp"
#include "bqt_log.hpp"

#include "bqt_exception.hpp"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    struct option long_flags[] = { { "devmode",       no_argument, NULL, 'd' },
                                   { "logfile", required_argument, NULL, 'l' } };
    
    std::string flags_list = "[ -d | --devmode ]          Enables developer mode options\n"
                             "[ -l | --logfile ] FILE     Sets a log file, none by default\n";
    
    // Engine options are immutable after parseLaunchArgs is called.
    bool        dev_mode;
    std::string log_file_name;
    
    std::ostream* log_stream;
}

/* bqt_launchargs.hpp *********************************************************//******************************************************************************/

namespace bqt
{
    void parseLaunchArgs( int argc, char* argv[] )
    {
        dev_mode      = LAUNCHVAL_DEVMODE;
        log_file_name = LAUNCHVAL_LOGFILE;
        
        log_stream = NULL;
        
        while( int flag = getopt_long( argc, argv, "dl:", long_flags, NULL ) != -1 )
        {
            switch( flag )
            {
            case 'd':
                dev_mode = true;
                break;
            case 'l':
                {
                    log_file_name = optarg;
                    if( log_stream != NULL )
                        delete log_stream;
                    
                    std::ofstream* log_file = new std::ofstream( log_file_name.c_str() );
                    if( log_file != NULL && !( log_file -> is_open() ) )
                        throw bqt::exception( "Could not open \'" + log_file_name + "\' to use as a log file" );
                    
                    log_stream = log_file;
                }
                break;
            default:
                throw bqt::exception( "Invalid flag specified; valid flags are:\n" + flags_list );
            }
        }
        
        if( log_stream == NULL )
            log_stream = &std::cout;
    }
    
    bool getDevMode()
    {
        return dev_mode;
    }
    std::string getLogFileName()
    {
        return log_file_name;
    }
}

/* bqt_log.hpp ****************************************************************//******************************************************************************/

namespace bqt
{
    std::ostream* getLogStream()
    {
        return log_stream;
    }
    
    void closeLog()
    {
        if( log_stream != NULL && log_stream != &std::cout )
            delete log_stream;
    }
}

