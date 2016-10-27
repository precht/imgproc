/**
 *      Purpose:
 *          Class contains basic image operations from task instruction
 *
 *      Created:    18th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#ifndef BASIC_UTILS_HPP
#define BASIC_UTILS_HPP

#include "img/Image.hpp"

namespace imgprocapp
{
namespace img
{
namespace utils
{

const int CONTRAST_CONST_POINT = 127;

class BasicUtils
{
  public:
    static void change_brightness(Image *image, int shift);
    static void change_contrast(Image *image, double slope);
    static void negate(Image *image);
  
  private:
    static void perform(Image *image, byte *pallete);
};

} // namespace utils 
} // namespace img
} // namespace imgprocapp

#endif // BASIC_UTILS_HPP
