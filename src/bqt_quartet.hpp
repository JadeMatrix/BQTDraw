#ifndef BQT_QUARTET_HPP
#define BQT_QUARTET_HPP

/* 
 * bqt_quartet.hpp
 * 
 * Data quartet struct for simplifying data access in file parsing
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

// #include <cstdint>

/******************************************************************************//******************************************************************************/

namespace bqt
{
    struct quartet
    {
        union
        {
            // uint8_t quarter[ 4 ];
            // uint16_t   half[ 2 ];
            // uint32_t   full[ 0 ];
        };
    };
    
    #define QUARTET_TAG( q ) q.quarter[ 0 ]
}

/******************************************************************************//******************************************************************************/

#endif

