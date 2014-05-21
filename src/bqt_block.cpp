/* 
 * bqt_block.cpp
 * 
 * Implements bqt_block.cpp
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_block.hpp"

#include "bqt_exception.hpp"
#include "bqt_taskexec.hpp"
#include "bqt_launchargs.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
/* BLOCK **********************************************************************//******************************************************************************/
    /* FRAME ******************************************************************//******************************************************************************/
    
    void block::frame::init( img_mode* mode, frame* previous )
    {
        this -> mode = mode;
        this -> previous = previous;
        
        // Does not allocate data, as it will be replaced soon anyways
    }
    
    block::frame::frame( img_mode* mode )
    {
        init( mode, NULL );
    }
    block::frame::frame( img_mode* mode, frame* previous )
    {
        init( mode, previous );
    }
    block::frame::frame( img_mode* mode, unsigned char* data )
    {
        this -> mode = mode;
        this -> previous = NULL;
        this -> data = data;
    }
    block::frame::~frame()
    {
        delete[] data;
    }
    
    /**************************************************************************//******************************************************************************/
    
    block::frame* block::getFrameFromTimestamp( timestamp stamp )
    {
        frame* current = frames;
        
        while( current != NULL )
        {
            if( current -> stamp == stamp )
                break;
            else
                current = current -> previous;
        }
        
        return current;
    }
    
    void block::pushBackFrames( timestamp stamp )
    {
        scoped_lock slock( block_mutex );
        
        frames -> stamp = stamp;
        
        frames = new block::frame( parent.getMode(), frames );
        
        delete redo_frames;
    }
    
    void block::shiftFrame( block::frame*& from, block::frame*& to )
    {
        if( from == NULL )
            return;
        
        block::frame* shift = from;
        
        from = shift -> previous;
        
        shift -> previous = to;
        
        to = shift;
    }
    bool block::undo()
    {
        scoped_lock slock( block_mutex );
        
        if( frames == NULL || frames -> previous == NULL )
            return false;
        else
        {
            shiftFrame( frames, redo_frames );
            return true;
        }
    }
    bool block::redo()
    {
        scoped_lock slock( block_mutex );
        
        if( redo_frames == NULL )
            return false;
        else
        {
            shiftFrame( redo_frames, frames );
            return true;
        }
    }
    
    block::block( layer& p, unsigned char* data ) : parent( p )
    {
        frames = new block::frame( parent.getMode(), data );
        redo_frames = NULL;
        
        channel_textures = NULL;
        
        submitTask( new UpdateBlockTexture_task( *this, stamp ) );
    }
    block::~block()
    {
        delete frames;
        delete redo_frames;
    }
    
/* UPDATEBLOCK_TASK ***********************************************************//******************************************************************************/
    
    UpdateBlock_task::UpdateBlock_task( block& b, timestamp stamp ) : target( b )
    {
        data = NULL;
        this -> stamp = stamp;
        
        submitTask( new PullBlockData_task( *this ) );
    }
    bool UpdateBlock_task::execute( task_mask* caller_mask )
    {
        scoped_lock slock( ubt_mutex );
        
        if( data == NULL )
            return false;
        else
        {
            scoped_lock slock( target.block_mutex );
            
            block::frame* ftu = target.getFrameFromTimestamp( stamp );
            
            if( ftu == NULL )
                throw exception( "UpdateBlock_task::execute(): Target block has no frame matching timestamp" );
            else
                ftu -> data = data;
            
            return true;
        }
    }
    
/* PULLBLOCKDATA_TASK *********************************************************//******************************************************************************/
    
    PullBlockData_task::PullBlockData_task( UpdateBlock_task& ubt ) : counterpart( ubt )
    {
        // Nothing else to do
    }
    bool PullBlockData_task::execute( task_mask* caller_mask )
    {
        scoped_lock slock( counterpart.ubt_mutex );
        
        if( counterpart.data != NULL )
            throw exception( "PullBlockData_task::execute(): Counterpart's data already filled" );
        
        counterpart.data = unpackBitmapFromGPU( counterpart.target.parent.getMode(),
                                                counterpart.target.channel_textures );
        
        return true;
    }
    
/* UPDATEBLOCKTEXTURE_TASK ****************************************************//******************************************************************************/
    
    UpdateBlockTexture_task::UpdateBlockTexture_task( block& b, timestamp stamp ) : source( b )
    {
        this -> stamp = stamp;
    }
    bool UpdateBlockTexture_task::execute( task_mask* caller_mask )
    {
        scoped_lock slock( source.block_mutex );
        
        if( stamp < source.stamp )
            return true;
        else
        {
            source.channel_textures = packBitmapToGPU( source.parent.getMode(),
                                                       source.channel_textures,
                                                       source.getFrameFromTimestamp( stamp ) -> data );
            
            return true;
        }
    }
}


