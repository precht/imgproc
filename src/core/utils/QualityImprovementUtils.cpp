/**
*      Created:    4th Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/Histogram.hpp"
#include "core/utils/BasicUtils.hpp"
#include "core/utils/QualityImprovementUtils.hpp"

//#include <iostream>

namespace imgproc
{
namespace core
{

void QualityImprovementUtils::uniformFinalProbabilityDensity(
        Image& image, Histogram& histogram, int output_min_level, int output_max_level)
{
    unsigned char pallete[Image::CHANNEL_RANGE];
    int sum = 0;
    for (int i = 0; i < Image::CHANNEL_RANGE; ++i)
    {
        sum += histogram.getLevel(i);
        pallete[i] = output_min_level + (output_max_level - output_min_level) * (double)sum / histogram.getImageChannelSize();
    }
    BasicUtils::perform(image, pallete);
}

} // core
} // imgproc

