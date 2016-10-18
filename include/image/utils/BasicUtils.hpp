/**
 *      Purpose:
 *          Class contains basic image operations from task instruction
 *
 *      Created:    18th Oct 2016
 *      Authors:    Jakub Precht
 */

#include "image/Image.hpp"

namespace imgprocapp
{
namespace image
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
    static void perform(Image *image, BYTE *pallete);
};

} // namespace utils 
} // namespace image
} // namespace imgprocapp

