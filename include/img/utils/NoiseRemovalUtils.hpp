/**
 *      Purpose:
 *          Class contains noise removal operations from task instruction
 *
 *      Created:    19th Oct 2016
 *      Authors:    Jakub Precht
 */

#ifndef NOISE_REMOVAL_UTILS_HPP
#define NOISE_REMOVAL_UTILS_HPP

#include "img/Image.hpp"
#include <vector>

namespace imgprocapp
{
namespace img
{
namespace utils
{

class NoiseRemovalUtils
{
  public:
    /* Radius specify the size of rectangle used to calculate new pixel value, it tell how manmy 
     * values consider around choosen pixel, by default it's 1, examples:
     * radius = 1, rectangle = 3x3; radius = 2, rectangle = 5x5; */
    static void geometric_mean_filter(Image *image, int radius = 1);
  
    /* Alpha tell how many extreme values drop before calculating mean value, it should be even 
     * and cannot be greater then the number of pixels in rectangle 
     * Radius specify the size of rectangle used to calculate new pixel value, it tell how manmy 
     * values consider around choosen pixel, by default it's 1, examples:
     * radius = 1, rectangle = 3x3; radius = 2, rectangle = 5x5; */
    static void alpha_trimmed_mean_filter(Image *image, unsigned alpha, int radius = 1);

  private:
    /* moves around the whole image and calculates new value for each pixel using provided filter
     * function, alpha parameter can be ommited if passed function do not use it (although defuault 
     * value 0 will be passed to that function */
    static void perform_core(Image *image, BYTE(*filter)(std::vector<BYTE>&, unsigned), int radius,
            int alpha = 0);

    static BYTE perform_geometric_mean_filter(std::vector<BYTE> &region, unsigned);
    static BYTE perform_alpha_trimmed_mean_filter(std::vector<BYTE> &region, unsigned alpha);
};

} // namespace utils 
} // namespace img
} // namespace imgprocapp

#endif // NOISE_REMOVAL_HPP


