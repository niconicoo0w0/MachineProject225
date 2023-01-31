/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#pragma once

class Image: public cs225::PNG {
    public:
        //increase luminance_
        void lighten(); 
        void lighten(double amount);

        //decrease luminance_
        void darken();  
        void darken(double amount);

        //increase saturation_
        void saturate();    
        void saturate(double amount);

        //decrease saturation_
        void desaturate();      
        void desaturate(double amount);

        void grayscale();  
        void rotateColor (double degrees);

        void illinify ();
        double illinifyHelper(double hue);

        void scale (double factor);
        void scale (unsigned w, unsigned h);
};

