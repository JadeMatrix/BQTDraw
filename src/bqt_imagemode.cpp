/* 
 * bqt_imagemode.cpp
 * 
 * Implements bqt_imagemode.hpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_imagemode.hpp"

#include <cmath>
#include <queue>

#include "bqt_exception.hpp"
#include "bqt_mutex.hpp"
#include "bqt_launchargs.hpp"

/* INTERNAL GLOBALS ***********************************************************//******************************************************************************/

namespace
{
    // We only ever need enough space for raw data for OpenGL to read/write for
    // the block size(s).
    std::queue< bqt::pack_space > pack_spaces;
    bqt::mutex pack_space_mutex;
}

/******************************************************************************//******************************************************************************/

namespace bqt
{
    /** BLOCK_TEXTURE *********************************************************//******************************************************************************/
    
    // void block_texture::unpackFromGPU()
    // {
    //     // TODO: implement
    // }
    // void block_texture::packToGPU()
    // {
    //     // TODO: implement
    // }
    
    /**************************************************************************//******************************************************************************/
    
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
    
    pack_space allocPackSpace()
    {
        scoped_lock slock( pack_space_mutex );
        
        pack_space got;
        
        if( pack_spaces.size() > 0 )
        {
            got = pack_spaces.front();
            pack_spaces.pop();
        }
        else
            got = new float[ 4 * ( int )pow( 2, getBlockExponent() * 2 ) ];     // No registration involved
        
        return got;
    }
    void releasePackSpace( pack_space s )
    {
        scoped_lock slock( pack_space_mutex );
        
        pack_spaces.push( s );
    }
    void cleanPackSpaces()
    {
        scoped_lock slock( pack_space_mutex );                                  // Thread safe so we can use it for debug, optimization, etc.
        
        while( !pack_spaces.empty() )
        {
            delete pack_spaces.front();
            pack_spaces.pop();
        }
    }
}


