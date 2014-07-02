/* 
 * bqt_fileformat.cpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_fileformat.hpp"

#include <fstream>

#include "bqt_quartet.hpp"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    
}

#define HEADER_FORWARD  0x00
#define HEADER_LAYER    0x80
#define HEADER_SKETCH   0x81
#define HEADER_NODE     0x82
#define HEADER_CHUNK    0x83
#define HEADER_FILL     0x84
#define HEADER_COLOR    0x85
#define HEADER_TEXTURE  0x86

/******************************************************************************//******************************************************************************/

namespace bqt
{
    enum bqt_parse_state
    {
        PS_FILE_HEADER,
        PS_FORWARD,
        PS_LAYER,
        PS_SKETCH,
        PS_NODE,
        PS_CHUNK,
        PS_FILL,
        PS_COLOR,
        PS_TEXTURE,
        PS_STRING
    };
    
    document* openBQTFile( const char* fn )
    {
        bqt_parse_state state = PS_FILE_HEADER;
        bool parsing = true;
        
        while( parsing )
        {
            switch( state )
            {
            case PS_FILE_HEADER:
                break;
            case PS_FORWARD:
                break;
            case PS_LAYER:
                break;
            case PS_SKETCH:
                break;
            case PS_NODE:
                break;
            case PS_CHUNK:
                break;
            case PS_FILL:
                break;
            case PS_COLOR:
                break;
            case PS_TEXTURE:
                break;
            case PS_STRING:
                break;
            }
        }
        
        return NULL;
    }
}


