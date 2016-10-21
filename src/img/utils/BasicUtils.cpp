/**
 *      Created:    18th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
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
    BYTE *pallete = new BYTE[COLORS_NUMBER];
    for(int i = 0; i < COLORS_NUMBER; ++i) 
    {
        if(i + shift < 0) pallete[i] = (BYTE)0;
        else if(i + shift >= COLORS_NUMBER) pallete[i] = (BYTE)(COLORS_NUMBER - 1);
        else pallete[i] = (BYTE)(i + shift);
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
        else if (value >= COLORS_NUMBER) value = COLORS_NUMBER - 1;
        pallete[i] = (BYTE)value;
    }
    perform(image, pallete);
    delete pallete;
}

void BasicUtils::negate(Image *image)
{
    change_contrast(image, -1);
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

