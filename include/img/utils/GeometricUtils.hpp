/**
 *      Purpose:
 *          Class contains geometric image operations from task instruction
 *
 *      Created:    18th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#ifndef GEOMETRIC_UTILS_HPP
#define GEOMETRIC_UTILS_HPP

#include "img/Image.hpp"

namespace imgprocapp
{
namespace img
{
namespace utils
{

class GeometricUtils
{
  public:
    static void flip_horizontally(Image *image);
    static void flip_vertically(Image *image);
    static void flip_diagonally(Image *image);
    static void scale(Image *image, double times);
  
  private:
    // linear functions  X = ax * X' + bx  and  Y = ay * Y' + by  define mapping from new image 
    // pixels to old ones; when size is a negative value it will be the same as in the old image
    static void perform(Image *image, double ax, double bx, double ay, double by, 
            int size_x = -1, int size_y = -1);
};

} // namespace utils 
} // namespace img
} // namespace imgprocapp

#endif // GEOMETRIC_UTILS_HPP


