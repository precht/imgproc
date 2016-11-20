/**
 *      Created:    19th Oct 2016
 *      Author:     Jakub Precht
 */

#ifndef ERROR_MEASURE_UTILS_HPP_
#define ERROR_MEASURE_UTILS_HPP_

#include "core/Image.hpp"

namespace imgproc
{
namespace core
{

class ErrorMeasureUtils
{
  public:
    static int maximumDifference(Image& orginal, Image& changed);
    static double meanSquareError(Image& orginal, Image& changed);
    static double peakMeanSquareError(Image& orginal, Image& changed);
    static double signalToNoiseRatio(Image& orginal, Image& changed);
    static double peakSignalToNoiseRatio(Image& orginal, Image& changed);

  private:
    enum ERROR_TYPE { MD, MSE, PMSE, SNR, PSNR };
    static double perform(Image& orginal, Image& changed, ERROR_TYPE type);
};

} // core
} // imgproc

#endif // ERROR_MEASURE_UTILS_HPP_


