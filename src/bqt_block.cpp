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
        
        data = allocBitmapSpace( mode, getBlockExponent(), ( previous ? previous -> data : NULL ) );
    }
    
    block::frame::frame( img_mode* mode )
    {
        init( mode, NULL );
    }
    block::frame::frame( img_mode* mode, frame* previous )
    {
        init( mode, previous );
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
    void block::undo()
    {
        scoped_lock slock( block_mutex );
        shiftFrame( frames, redo_frames );
    }
    void block::redo()
    {
        scoped_lock slock( block_mutex );
        shiftFrame( redo_frames, frames );
    }
    
    block::block( layer& p ) : parent( p )
    {
        // TODO: implement
        
        frames = new block::frame( parent.getMode() );
        redo_frames = NULL;
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
            {
                // TODO: implement
            }
            
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
        
        // TODO: implement
        
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
            // TODO: implement
            
            return true;
        }
    }
}


