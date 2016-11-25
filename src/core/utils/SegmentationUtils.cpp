/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"
#include "core/utils/SegmentationUtils.hpp"

#include <stdexcept>

namespace imgproc
{
namespace core
{

void SegmentationUtils::regionGrowing(Image& image, int seed_row, int seed_column, const StructuralElement& element,
                                      bool (*condition)(unsigned char, unsigned char, int, int),
                                      int lower_condition_coefficient, int higher_condition_coefficient)
{
    if(seed_row < 0) throw std::invalid_argument("seed row cannot be negative");
    if(seed_column < 0) throw std::invalid_argument("seed column cannot be negative");
    if(seed_row >= image.rows())
        throw std::invalid_argument("seed row has to be smaller then image rows number");
    if(seed_column >= image.columns())
        throw std::invalid_argument("seed column has to be smaller then image columns number");

    // TODO
}

void SegmentationUtils::deltaRegionGrowing(Image& image, int seed_row, int seed_column, const StructuralElement& element,
                                           int lower_delta, int higher_delta)
{
    regionGrowing(image, seed_row, seed_column, element, deltaCondition, lower_delta, higher_delta);
}

void SegmentationUtils::rangeRegionGrowing(Image& image, int seed_row, int seed_column, const StructuralElement& element,
                                           int lower_value, int higher_value)
{
    regionGrowing(image, seed_row, seed_column, element, rangeCondition, lower_value, higher_value);
}

bool SegmentationUtils::deltaCondition(unsigned char seed, unsigned char candidate, int lower_delta, int higher_delta)
{
    // TODO
    return false;
}

bool SegmentationUtils::rangeCondition(unsigned char seed, unsigned char candidate, int lower_value, int higher_value)
{
    // TODO
    return false;
}



} // core
} // imgproc
