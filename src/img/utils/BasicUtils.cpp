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
    byte *pallete = new byte[COLORS_NUMBER];
    for(int i = 0; i < COLORS_NUMBER; ++i) 
    {
        if(i + shift < 0) pallete[i] = (byte)0;
        else if(i + shift >= COLORS_NUMBER) pallete[i] = (byte)(COLORS_NUMBER - 1);
        else pallete[i] = (byte)(i + shift);
    }
    perform(image, pallete);
    delete pallete;
}

void BasicUtils::change_contrast(Image *image, double slope)
{
    double shift = CONTRAST_CONST_POINT * (1 - slope);
    byte *pallete = new byte[COLORS_NUMBER];
    for(unsigned i = 0; i < COLORS_NUMBER; ++i) 
    {
        double value = slope * i + shift;
        if(value < 0) value = 0;
        else if (value >= COLORS_NUMBER) value = COLORS_NUMBER - 1;
        pallete[i] = (byte)value;
    }
    perform(image, pallete);
    delete pallete;
}

// change_contrast -1 is not as precise as explicite bit negation (because of doubles?)
void BasicUtils::negate(Image *image)
{
    byte *pallete = new byte[COLORS_NUMBER];
    for(unsigned i = 0; i < COLORS_NUMBER; ++i) pallete[i] = ~((byte)i);
    BasicUtils::perform(image, pallete);
    delete pallete;
}

void BasicUtils::perform(Image *image, byte *pallete)
{
    for(int x = 0; x < image->rows(); ++x)
    {
        for(int y = 0; y < image->columns(); ++y)
        {
            for(int c = 0; c < image->channels(); ++c)
            {
                byte *b = image->ptr(x, y, c);
                *b = pallete[*b];
            }
        }
    }
}

} // namespace utils 
} // namespace img
} // namespace imgprocapp

