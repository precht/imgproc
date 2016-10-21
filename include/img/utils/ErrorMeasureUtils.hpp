/**
 *      Purpose:
 *          Class contains error measure operations from task instruction
 *
 *      Created:    19th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#ifndef ERROR_MEASURE_HPP
#define ERROR_MEASURE_HPP

#include "img/Image.hpp"

namespace imgprocapp
{
namespace img
{
namespace utils
{

class ErrorMeasureUtils
{
  public:
    static int maximum_difference(Image *orginal, Image *changed);
    static double mean_square_error(Image *orginal, Image *changed);
    static double peak_mean_square_error(Image *orginal, Image *changed);
    static double signal_to_noise_ratio(Image *orginal, Image *changed);
    static double peak_signal_to_noise_ratio(Image *orginal, Image *changed);

  private:
    enum ERROR_TYPE { MD, MSE, PMSE, SNR, PSNR };
    static double perform(Image *orginal, Image *changed, ERROR_TYPE type);
};

} // namespace utils 
} // namespace img
} // namespace imgprocapp

#endif // ERROR_MEASURE_HPP


