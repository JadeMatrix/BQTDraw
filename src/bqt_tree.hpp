#ifndef BQT_TREE_HPP
#define BQT_TREE_HPP

/* 
 * bqt_tree.hpp
 * 
 * Tree utility class template
 * For storage only, accessing is left up to whatever uses it
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/

#include <cstddef>

/******************************************************************************//******************************************************************************/

namespace bqt
{
    template< typename T, unsigned int N > class tree
    {
    public:
        class node
        {
        public:
            T data;
            node* branch[ N ];
            
            node( T data )
            {
                this -> data = data;
                
                for( int i = 0; i < N; i++ )
                    branch[ i ] = NULL;
            }
            ~node()
            {
                for( int i = 0; i < N; i++ )
                    delete branch[ i ];
            }
        };
        
        node* root;
        
        tree()
        {
            root = NULL;
        }
        tree( T data )
        {
            root = new node( data );
        }
        ~tree()
        {
            if( root != NULL )
                delete root;
        }
    };
}

/******************************************************************************//******************************************************************************/

#endif


