/**
 *      Created:    19th Oct 2016
 *      Author:     Jakub Precht
 */

#ifndef NOISE_REMOVAL_UTILS_HPP_
#define NOISE_REMOVAL_UTILS_HPP_

#include "core/Image.hpp"
#include <vector>

namespace imgproc
{
namespace core
{

class NoiseRemovalUtils
{
  public:
    /* Radius specify the size of rectangle used to calculate new pixel value, it tell how many 
     * values consider around choosen pixel, by default it's 1, examples:
     * radius = 1, rectangle = 3x3; radius = 2, rectangle = 5x5; */
    static void geometricMeanFilter(Image& image, const int radius = 1);

    /* Alpha tell how many extreme values drop from one side (max and respectivly min) when 
     * calculating mean value, it cannot be greater then the number of pixels in rectangle 
     * Radius specify the size of rectangle used to calculate new pixel value, it tell how many 
     * values consider around choosen pixel, by default it's 1, examples:
     * radius = 1, rectangle = 3x3; radius = 2, rectangle = 5x5; */
    static void alphaTrimmedMeanFilter(Image& image, const int alpha, const int radius = 1);

  private:
    /* moves around the whole image and calculates new value for each pixel using provided filter
     * function, alpha parameter can be ommited if passed function do not use it (although defuault 
     * value 0 will be passed to that function */
    static void perform(Image& image, unsigned char(*filter)(std::vector<unsigned char>&, const int),
            const int radius, const int alpha = 0);

    static unsigned char geometricMeanFilterPerformer(std::vector<unsigned char>& region, const int);
    static unsigned char alphaTrimmedMeanFilterPerformer(std::vector<unsigned char>& region, const int alpha);
};

} // core
} // imgproc

#endif // NOISE_REMOVAL_UTILS_HPP_


