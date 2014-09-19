#include <math.h>
#include "gl.h"

void drawCircle( double x, double y, double r )
{
    int faces = 1;
    
    double dtheta = 360.0f / faces;
    
    glBegin( GL_POLYGON );
    {
        for( int i = 0; i < faces; ++i )
        {
            double theta = dtheta * i;
            glVertex2f( cos( theta ), sin( theta ) );
        }
    }
    glEnd();
    
    return;
    
    // Avoid floating point error buildup, may be slower:
    
    glBegin( GL_POLYGON );
    {
        for( int i = 0; i < faces; ++i )
        {
            double theta = 360.0f * ( i / ( double )faces );
            glVertex2f( cos( theta ), sin( theta ) );
        }
    }
    glEnd();
}

// Assumes the first circle has been drawn

void connectCircles( double x1, double y1, double r1,
                     double x2, double y2, double r2 )
{
    double r3 = r1 - r2;
    
    double dx = x2 - x1;
    double dy = y2 - y1;
    
    double d  = sqrt( dx * dx + dy * dy );
    
    if( r3 + d > 0 && r3 - d < 0 )
    {
        double phi   = atan2(  dy, dx );
        double theta = arccos( r3 / d );
        
        double small = theta - phi;
        double big   = theta + phi * -1.0f;
        
        glBegin( GL_QUADS );
        {
            glVertex2f( x1 + r1 * cos( small ), y1 + r1 * sin( small ) );
            glVertex2f( x2 + r2 * cos( small ), y2 + r2 * sin( small ) );
            glVertex2f( x2 + r2 * cos( big   ), y2 + r2 * sin( big   ) );
            glVertex2f( x1 + r1 * cos( big   ), y1 + r1 * sin( big   ) );
        }
        glEnd();
        
        drawCircle( x2, y2, r2 );
    }
    // No else case, as this function is designed for interpolating size only
}