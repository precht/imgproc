/**
 *      Purpose:
 *          Class contains linear filtration methods (task 2)
 *
 *      Created:    4th Nov 2016
 *      Author:  Jakub Precht
 */

#ifndef LINEAR_FILTRATION_UTILS_HPP_
#define LINEAR_FILTRATION_UTILS_HPP_

#include "img/Image.hpp"
#include "img/Histogram.hpp"

namespace imgprocapp {
namespace img {
namespace utils {

class LinearFiltrationUtils
{
  public:
    const static int MASK_EDGE = 3;
    const static int MASK_SIZE = MASK_EDGE * MASK_EDGE;
    static void lineIdentification(Image *image);
    static void perform(Image *image, int mask[MASK_SIZE]);

  private:
    static void flipMask(int mask[]);
};

} // namespace utils
} // namespace img
} // namespace imgprocapp

#endif // LINEAR_FILTRATION_UTILS_HPP_
