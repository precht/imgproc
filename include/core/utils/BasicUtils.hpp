/**
 *      Created:    18th Oct 2016
 *      Author:     Jakub Precht
 */

#ifndef BASIC_UTILS_HPP
#define BASIC_UTILS_HPP

#include "core/Image.hpp"

namespace imgproc
{
namespace core
{


class BasicUtils
{
  public:
    static void brightness(Image& image, int shift);
    static void contrast(Image& image, double slope);
    static void negate(Image& image);
    static void perform(Image& image, unsigned char *pallete);

private:
    const static int CONTRAST_CONST_POINT = 127;
};


} // core
} // imgproc

#endif // BASIC_UTILS_HPP
