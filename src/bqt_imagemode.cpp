/* 
 * bqt_imagemode.cpp
 * 
 * Implements bqt_imagemode.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_imagemode.hpp"

#include <cmath>

#include "bqt_exception.hpp"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    // Swap space for packing/unpacking?
}

/******************************************************************************//******************************************************************************/

namespace bqt
{
    unsigned char* allocBitmapSpace( img_mode* mode,
                                     unsigned char exponent,
                                     unsigned char* original )
    {
        if( mode == NULL || exponent < BLOCKEXPONENT_MIN || exponent > BLOCKEXPONENT_MAX )
            throw exception( "allocBitmapSpace(): Invalid parameters" );
        
        if( mode -> channels < 1 || mode -> depth < 1 )
            throw exception( "allocBitmapSpace(): Invalid mode" );
        
        double bytes_d = ( double )( mode -> channels * mode -> depth ) / 8.0;
        
        if( bytes_d > ( pow( 2, sizeof( unsigned int ) ) - 1 ) )
            throw exception( "allocBitmapSpace(): Required space too large" );
        
        unsigned int bytes_i = ( unsigned int )ceil( bytes_d );
        
        unsigned char* data = new unsigned char[ bytes_i ];
        
        if( original != NULL )
        {
            for( unsigned int i = 0; ; i++ )                                    // We don't check i < bytes_i because bytes_i could be MAX_UINT
            {
                data[ i ] = original[ i ];
                
                if( i + 1 == bytes_i )                                          // Wrap-safe; we've already checked to make sure it won't overflow
                    break;
            }
        }
        
        return data;
    }
}


