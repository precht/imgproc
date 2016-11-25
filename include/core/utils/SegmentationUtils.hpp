/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#ifndef SEGMENTATION_UTILS_HPP_
#define SEGMENTATION_UTILS_HPP_

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"

namespace imgproc
{
namespace core
{

class SegmentationUtils
{
public:
    static void regionGrowing(Image& image, int seed_row, int seed_column, const StructuralElement& element,
                              bool(*condition)(unsigned char seed, unsigned char candidate, int, int),
                              int lower_condition_coefficient, int higher_condition_coefficient);

    // lower and higer delta specify how much can candidate differ from seed
    static void deltaRegionGrowing(Image& image, int seed_row, int seed_column, const StructuralElement& element,
                                   int lower_delta, int higher_delta);

    // lower and higher value specify exact range that seed and candidate must be in
    static void rangeRegionGrowing(Image& image, int seed_row, int seed_column, const StructuralElement& element,
                                   int lower_value, int higher_value);

private:
    static bool deltaCondition(unsigned char seed, unsigned char candidate, int lower_delta, int higher_delta);
    static bool rangeCondition(unsigned char seed, unsigned char candidate, int lower_value, int higher_value);
};

} // core
} // imgproc

#endif // SEGMENTATION_UTILS_HPP_
