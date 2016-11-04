/**
*      Created:    4th Nov 2016
*      Author:     Jakub Precht
*/

#include "img/utils/BasicUtils.hpp"
#include "img/utils/QualityImprovementUtils.hpp"
#include <iostream>

namespace imgprocapp
{
namespace img
{
namespace utils
{
void QualityImprovementUtils::uniformFinalProbabilityDensity(Image *image, Histogram &histogram, int output_min_level,
                                                             int output_max_level)
{
    byte pallete[COLORS_NUMBER];
    int sum = 0;
    for (int i = 0; i < COLORS_NUMBER; ++i)
    {
        sum += histogram.getLevel(i);
        pallete[i] = output_min_level + (output_max_level - output_min_level) * (double)sum / histogram.getPixels();
    }
    BasicUtils::perform(image, pallete);
}

} // namespace utils
} // namespace img
} // namespace imgprocapp
