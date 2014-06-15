#ifndef BQT_SKETCH_HPP
#define BQT_SKETCH_HPP

/* 
 * bqt_sketch.hpp
 * 
 * About
 * 
 */

/* INCLUDES *******************************************************************//******************************************************************************/



/******************************************************************************//******************************************************************************/

namespace bqt
{
    class sketch : public trackable
    {
    protected:
        layer& parent
        std::vector< std::vector< block* > > blocks; 
    public:
        // sketch( img_mode& m, long w, long h /*, file_layer*? fl = NULL */ );
        // ~sketch();
        sketch( layer& p );
        
        img_mode& getMode();
        
        int cc( int c );                                                        // "ConvertCoordinate()," short name since it will be used repetitively
    };
}

/******************************************************************************//******************************************************************************/

#endif


