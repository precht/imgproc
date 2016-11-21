/**
 *      Created:    4th Nov 2016
 *      Author:     Jakub Precht
 */

#ifndef QUALITY_IMPROVEMENT_UTILS_HPP_
#define QUALITY_IMPROVEMENT_UTILS_HPP_

#include "core/Image.hpp"
#include "core/Histogram.hpp"

namespace imgproc
{
namespace core
{

class QualityImprovementUtils
{
    const static int DEFAULT_MIN = 0;
    const static int DEFAULT_MAX = Image::CHANNEL_RANGE;

public:
    static void uniformFinalProbabilityDensity(Image& image, Histogram& histogram, int output_min_level = DEFAULT_MIN,
                                               int output_max_level = DEFAULT_MAX);
};

} // core
} // imgproc

#endif // QUALITY_IMPROVEMENT_UTILS_HPP_
