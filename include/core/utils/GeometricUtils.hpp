/**
 *      Created:    18th Oct 2016
 *      Author:     Jakub Precht
 */

#ifndef GEOMETRIC_UTILS_HPP
#define GEOMETRIC_UTILS_HPP

#include "core/Image.hpp"

namespace imgproc
{
namespace core
{

class GeometricUtils
{
  public:
    static void horizontalFlip(Image& image);
    static void verticalFlip(Image& image);
    static void diagonalFlip(Image& image);
    static void scale(Image& image, double times);
  
  private:
    // linear functions  X = ax * X' + bx  and  Y = ay * Y' + by  define mapping from new image 
    // pixels to old ones; when size is a negative value it will be the same as in the old image
    static void perform(Image& image, double ax, double bx, double ay, double by,
            int size_x = -1, int size_y = -1);
};

} // core
} // imgproc

#endif // GEOMETRIC_UTILS_HPP


