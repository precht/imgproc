/**
 *      Created:    4th Nov 2016
 *      Author:     Jakub Precht
 */

#ifndef LINEAR_FILTRATION_UTILS_HPP_
#define LINEAR_FILTRATION_UTILS_HPP_

#include "core/Image.hpp"
#include "core/Histogram.hpp"

namespace imgproc
{
namespace core
{

class LinearFiltrationUtils
{
  public:
    static const int MASK_EDGE = 3;
    static const int MASK_SIZE = MASK_EDGE * MASK_EDGE;
    // uses best mask and has optimalizations
    static void lineIdentification(Image& image);
    // switches between defferent line identification masks and use perform method
    // there are 4 possible masks variations (id form 1 to 4)
    static void lineIdentification(Image& image, const int id);
    // perform linear filtration on image using mask
    static void perform(Image& image, const int mask[MASK_SIZE]);

  private:
    static const int LINE_IDENTIFICATION_MASK_1_[MASK_SIZE];
    static const int LINE_IDENTIFICATION_MASK_2_[MASK_SIZE];
    static const int LINE_IDENTIFICATION_MASK_3_[MASK_SIZE];
    static const int LINE_IDENTIFICATION_MASK_4_[MASK_SIZE];
};

} // core
} // imgproc

#endif // LINEAR_FILTRATION_UTILS_HPP_
