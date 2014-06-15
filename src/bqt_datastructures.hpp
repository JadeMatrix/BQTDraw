#ifndef BQT_DATASTRCUTURES_HPP
#define BQT_DATASTRCUTURES_HPP

/* 
 * bqt_datastructures.hpp
 * 
 * Contains class predeclarations & other useful stuff for internal data storage
 * structures.  Block size, hereafter called bsize, means a 2^n x 2^n pixel
 * square, where n is some exponent chosen or set at program launch.
 * 
 * Block:
 * A bsize-subsection of a sketch, containing the pixel data for that block's
 * channels as well as a comp texture for rendering.
 * Tracks:
 * pixel edits
 * 
 * Slice:
 * A temporary data structure created whenever dynamic changes are being made to
 * a block.  Slices link to the block as well as all overlapping blocks in all
 * sketches.  Slices are discarded as soon as the changes are saved to the zoom
 * comp texture & written back to the block.
 * 
 * Sketch:
 * Basically a sub-layer, sketches allow multiple revisions of a layer to be
 * onion-skinned.  The top sketch is the main drawing on that layer and is the
 * only one that can be edited at a given time.  Sketches can have a different
 * DPI than their parent layer, but it must be 1/(2^n) of the parent DPI for
 * some exponent n, and the apparent image size remains the same.
 * Tracks:
 * mode changes (channel count, DPI)
 * 
 * Layer:
 * A collection of sketches, at least one of which is visible.  Contains the
 * base DPI for the sketch collection, the document offset, and the downsampling
 * method to be used on export if the layer is a higher DPI than the canvas.
 * Tracks:
 * sketch switching/relayering (DPI changes tracked by children)
 * 
 * Canvas (Document):
 * 
 * 
 */

/******************************************************************************//******************************************************************************/

namespace bqt
{
    class block;
    class slice;
    class sketch;
    class layer;
    class canvas;
}

/******************************************************************************//******************************************************************************/

#endif


