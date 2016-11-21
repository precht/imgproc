/**
*      Created:    10th Nov 2016
*      Author:     Jakub Precht
*/

#ifndef NON_LINEAR_FILTRATION_UTILS_HPP_
#define NON_LINEAR_FILTRATION_UTILS_HPP_

#include "core/Image.hpp"
#include "core/Histogram.hpp"

namespace imgproc
{
namespace core
{

class NonLinearFiltrationUtils
{
public:
    static void uolis(Image& image);
};

} // core
} // imgproc

#endif // NON_LINEAR_FILTRATION_UTILS_HPP_
