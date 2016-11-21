/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#ifndef SEGMENTATION_UTILS_HPP_
#define SEGMENTATION_UTILS_HPP_

#include "core/Image.hpp"

namespace imgproc
{
namespace core
{

class SegmentationUtils
{
public:
    static void regionGrowing(Image& image);
};

} // core
} // imgproc

#endif // SEGMENTATION_UTILS_HPP_
