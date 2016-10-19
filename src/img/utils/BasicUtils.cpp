/**
 *      Created:    18th Oct 2016
 *      Author:     Jakub Precht
 */

#include "img/utils/BasicUtils.hpp"

namespace imgprocapp
{
namespace img
{
namespace utils
{

void BasicUtils::change_brightness(Image *image, int shift)
{
    // TODO prop except
    BYTE *pallete = new BYTE[COLORS_NUMBER];
    if(shift < 0) 
    {
        if(-shift >= COLORS_NUMBER) throw "BasicUtils: Brightness shift out of range";
        for(int i = 0; i < COLORS_NUMBER; ++i) 
        {
            if(i + shift < 0) pallete[i] = (BYTE)0;
            else pallete[i] = (BYTE)(i + shift);
        }
    }
    else
    {
        if(shift >= COLORS_NUMBER) throw "BasicUtils: Brightness shift out of range";
        for(int i = 0; i < COLORS_NUMBER; ++i) 
        {
            if(i + shift > COLORS_NUMBER - 1) pallete[i] = (BYTE)(COLORS_NUMBER - 1);
            else pallete[i] = (BYTE)(i + shift);
        }
    }
    perform(image, pallete);
    delete pallete;
}

void BasicUtils::change_contrast(Image *image, double slope)
{
    double shift = CONTRAST_CONST_POINT * (1 - slope);
    BYTE *pallete = new BYTE[COLORS_NUMBER];
    for(unsigned i = 0; i < COLORS_NUMBER; ++i) 
    {
        double value = slope * i + shift;
        if(value < 0) value = 0;
        else if (value > COLORS_NUMBER - 1) value = COLORS_NUMBER - 1;
        pallete[i] = (BYTE)value;
    }
    perform(image, pallete);
    delete pallete;
}

void BasicUtils::negate(Image *image)
{
    // it turns out that this method isn't really faster then contrast with slope=-1
    // let's use it instead
    change_contrast(image, -1);

    // BYTE *pallete = new BYTE[COLORS_NUMBER];
    // for(unsigned i = 0; i < COLORS_NUMBER; ++i) pallete[i] = ~((BYTE)i);
    // perform(image, pallete);
    // delete pallete;
}

void BasicUtils::perform(Image *image, BYTE *pallete)
{
    for(int x = 0; x < image->rows(); ++x)
    {
        for(int y = 0; y < image->columns(); ++y)
        {
            for(int c = 0; c < image->channels(); ++c)
            {
                BYTE *b = image->ptr(x, y, c);
                *b = pallete[*b];
            }
        }
    }
}

} // namespace utils 
} // namespace img
} // namespace imgprocapp

