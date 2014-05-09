/* 
 * bqt_thread.cpp
 * 
 * Implements the bqt::thread class from bqt_thread.hpp using pthreads
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include "bqt_thread.hpp"

#include "bqt_exception.hpp"

/******************************************************************************//******************************************************************************/

namespace bqt
{
    void thread::createPThread( thread_func function, void* data )
    {
        if( has_thread )
            throw bqt::exception( "bqt::thread::createPThread(): Thread already running" );
        if( function == NULL )
            throw bqt::exception( "bqt::thread::createPThread(): function is NULL" );
        
        pthread_attr_init( &pt_attr );
        pthread_attr_setdetachstate( &pt_attr, PTHREAD_CREATE_JOINABLE );       // Create a 'joinable' attribute for the thread
        
        if( pthread_create( &pt_thread, &pt_attr, function, data ) )
            has_thread = false;
        else
            has_thread = true;
    }
    
    void thread::kill()
    {
        if( has_thread )
            pthread_cancel( pt_thread );
    }
    
    thread::thread()
    {
        has_thread = false;
        
        function = NULL;
        data = NULL;
    }
    thread::thread( thread_func function )
    {
        has_thread = false;
        
        this -> function = function;
        data = NULL;
    }
    thread::thread( void* data )
    {
        has_thread = false;
        
        function = NULL;
        this -> data = data;
    }
    thread::thread( thread_func function, void* data )
    {
        has_thread = false;
        
        this -> function = function;
        this -> data = data;
    }
    thread::~thread()
    {
        kill();
    }
    
    void thread::setFunction( thread_func function )
    {
        this -> function = function;
    }
    void thread::setData( void* data )
    {
        this -> data = data;
    }
    
    bool thread::start()
    {
        createPThread( function, data );
        
        return has_thread;
    }
    bool thread::start( thread_func function )
    {
        createPThread( function, data );
        
        return has_thread;
    }
    bool thread::start( void* data )
    {
        createPThread( function, data );
        
        return has_thread;
    }
    bool thread::start( thread_func function, void* data )
    {
        createPThread( function, data );
        
        return has_thread;
    }
    
    exit_code thread::wait()
    {
        exit_code return_value;
        
        pthread_join( pt_thread, &return_value );
        has_thread = false;
        
        return return_value;
    }
}


