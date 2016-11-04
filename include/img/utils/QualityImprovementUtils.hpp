/**
 *      Purpose:
 *          Class contains image quality improvement methods based on image's histogram.
 *
 *      Created:    4th Nov 2016
 *      Author:     Jakub Precht
 */

#ifndef QUALITY_IMPROVEMENT_UTILS_
#define QUALITY_IMPROVEMENT_UTILS_

#include "img/Image.hpp"
#include "img/Histogram.hpp"

namespace imgprocapp
{
namespace img
{
namespace utils
{

class QualityImprovementUtils
{
  public:
    const static int DEFAULT_MIN = 0;
    const static int DEFAULT_MAX = COLORS_NUMBER;
    static void uniformFinalProbabilityDensity(Image *image, Histogram &histogram, int output_min_level = DEFAULT_MIN,
                                               int output_max_level = DEFAULT_MAX);
};

} // namespace utils
} // namespace img
} // namespace imgprocapp

#endif // QUALITY_IMPROVEMENT_UTILS_
