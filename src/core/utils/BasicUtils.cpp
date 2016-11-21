/**
 *      Created:    18th Oct 2016
 *      Author:     Jakub Precht
 */

#include "core/utils/BasicUtils.hpp"

namespace imgproc
{
namespace core
{

void BasicUtils::brightness(Image& image, int shift)
{
    unsigned char *pallete = new unsigned char[Image::CHANNEL_RANGE];
    for(int i = 0; i < Image::CHANNEL_RANGE; ++i)
    {
        if(i + shift < 0) pallete[i] = (unsigned char)0;
        else if(i + shift >= Image::CHANNEL_RANGE) pallete[i] = (unsigned char)(Image::CHANNEL_RANGE - 1);
        else pallete[i] = (unsigned char)(i + shift);
    }
    perform(image, pallete);
    delete[] pallete;
}

void BasicUtils::contrast(Image& image, double slope)
{
    double shift = CONTRAST_CONST_POINT * (1 - slope);
    unsigned char *pallete = new unsigned char[Image::CHANNEL_RANGE];
    for(unsigned i = 0; i < Image::CHANNEL_RANGE; ++i)
    {
        double value = slope * i + shift;
        if(value < 0) value = 0;
        else if (value >= Image::CHANNEL_RANGE) value = Image::CHANNEL_RANGE - 1;
        pallete[i] = (unsigned char)value;
    }
    perform(image, pallete);
    delete[] pallete;
}

// change_contrast -1 is not as precise as explicite bit negation (because of doubles?)
void BasicUtils::negate(Image& image)
{
    unsigned char *pallete = new unsigned char[Image::CHANNEL_RANGE];
    for(unsigned i = 0; i < Image::CHANNEL_RANGE; ++i) pallete[i] = ~((unsigned char)i);
    BasicUtils::perform(image, pallete);
    delete[] pallete;
}

void BasicUtils::perform(Image& image, unsigned char *pallete)
{
    for(int x = 0; x < image.rows(); ++x)
        for(int y = 0; y < image.columns(); ++y)
            for(int c = 0; c < image.channels(); ++c)
            {
                unsigned char &b = image(x, y, c);
                b = pallete[b];
            }
}


} // core
} // imgproc

