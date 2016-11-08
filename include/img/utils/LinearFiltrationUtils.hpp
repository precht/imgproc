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
    static const int MASK_EDGE = 3;
    static const int MASK_SIZE = MASK_EDGE * MASK_EDGE;
    static void lineIdentification(Image &image);
    static void perform(Image &image, const int mask[MASK_SIZE]);

  private:
    static const int LINE_IDENTIFICATION_MASK_1_[MASK_SIZE];
    static const int LINE_IDENTIFICATION_MASK_2_[MASK_SIZE];
    static const int LINE_IDENTIFICATION_MASK_3_[MASK_SIZE];
    static const int LINE_IDENTIFICATION_MASK_4_[MASK_SIZE];
};

} // namespace utils
} // namespace img
} // namespace imgprocapp

#endif // LINEAR_FILTRATION_UTILS_HPP_
