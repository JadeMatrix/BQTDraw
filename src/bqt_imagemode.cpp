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
#include "threading/bqt_mutex.hpp"
#include "bqt_preferences.hpp"

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
    raw allocBitmapSpace( img_mode* mode,
                          raw original )
    {
        unsigned char exponent = getBlockExponent();
        
        if( mode == NULL || exponent < BLOCKEXPONENT_MIN || exponent > BLOCKEXPONENT_MAX )
            throw exception( "allocBitmapSpace(): Invalid parameters" );
        
        if( mode -> channel_count < 1 || mode -> depth < 1 )
            throw exception( "allocBitmapSpace(): Invalid mode" );
        
        double bytes_d = ( double )( mode -> channel_count * mode -> depth ) / 8.0;
        
        if( bytes_d > ( pow( 2, sizeof( unsigned int ) ) - 1 ) )
            throw exception( "allocBitmapSpace(): Required space too large" );
        
        unsigned int bytes_i = ( unsigned int )ceil( bytes_d );
        
        raw data = new unsigned char[ bytes_i ];
        
        if( data == NULL )
            throw exception( "allocBitmapSpace(): Out of memory" );
        
        if( original != NULL )
        {
            for( unsigned int i = 0; ; ++i )                                    // We don't check i < bytes_i because bytes_i could be MAX_UINT
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
        scoped_lock< mutex > slock( pack_space_mutex );
        
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
        scoped_lock< mutex > slock( pack_space_mutex );
        
        pack_spaces.push( s );
    }
    void cleanPackSpaces()
    {
        scoped_lock< mutex > slock( pack_space_mutex );                                  // Thread safe so we can use it for debug, optimization, etc.
        
        while( !pack_spaces.empty() )
        {
            delete pack_spaces.front();
            pack_spaces.pop();
        }
    }
    
    raw convertRawPixels( raw source, raw target, img_mode& from, img_mode& to )
    {
        // if( from.depth > 8 * sizeof( long ) || from.depth < 1 )
        //     throw exception( "convertRawPixels(): Source mode out of acceptable range" );
        // if( to.depth > 8 * sizeof( long ) || to.depth < 1 )
        //     throw exception( "convertRawPixels(): Target mode out of acceptable range" );
        
        // if( source == NULL )
        //     throw exception( "convertRawPixels(): Source is NULL" );
        
        // unsigned long from_max = exp( 2, from.depth ) - 1;                      // Max value per channel for from
        // unsigned long   to_max = exp( 2,   to.depth ) - 1;                      // Max value per channel for to
        
        // if( target == NULL )
        //     raw = allocBitmapSpace( &to, NULL );                                // Allocate new space if needed; will throw exception on fail
        
        // unsigned long buffer = 0x00;
        // unsigned long source_bit_count = from.depth * from.channel_count;
        // raw source_iter = source;
        
        // // to_value = ( unsigned long )round( ( ( double )from_value / ( double )from_fill ) * ( double )to_fill )
        // // to_value = from_value << to_value - from_value;
        
        // unsigned long from_mask = ~( -1 >> from.depth );
        // unsigned char* from_mask_mask = ( unsigned char* )&from_mask;
        // int from_mask_mask_offset = 0;
        
        // for( unsigned long i = 0; i < source_bit_count; )
        // {
        //     buffer |= *source_iter | from_mask_mask[ from_mask_mask_offset ];
            
        //     from_mask_mask_offset = ( from_mask_mask_offset + 1 ) % sizeof( long );
            
        //     if( from_mask_mask_offset == 0 )                                    // We looped around, so we're at the trailing end of the mask, so...
        //     {
        //         buffer >>= from.depth % 8;                                      // ... shift the buffer backwards to cover that
                
        //         for( int j = 0; j < sizeof( double ); j++ )                     // The buffer is ready now, so begin writing it
        //         {
        //             #if defined CONVERT_RAW_SCALE
                    
                    
                    
        //             #elif defined CONVERT_RAW_
        //         }
                
        //         buffer = 0x00;                                                  // Clear the buffer
                
        //         i += from.depth % 8;
        //     }
        //     else
        //         i += 8;
        // }
        
        throw exception( "convertRawPixels(): Not implemented" );
        // TODO: implement
        
        return NULL;
    }
}


