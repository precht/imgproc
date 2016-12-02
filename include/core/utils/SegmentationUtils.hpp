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
    static void regionGrowing(Image& image, int seed_row, int seed_column,
                              bool(*condition)(unsigned char seed, unsigned char candidate, int, int),
                              const int lower_condition_coefficient, const int higher_condition_coefficient,
                              const StructuralElement& element = plus_se );

    // lower and higer delta specify how much can candidate differ from seed
    static void deltaRegionGrowing(Image& image, int seed_row, int seed_column,
                                   const int lower_delta, const int higher_delta,
                                   const StructuralElement& element = plus_se);

    // lower and higher value specify exact range that seed and candidate must be in
    static void rangeRegionGrowing(Image& image, int seed_row, int seed_column,
                                   const int lower_value, const int higher_value,
                                   const StructuralElement& element = plus_se);

private:
    static bool deltaCondition(unsigned char seed, unsigned char candidate,
                               const int lower_delta, const int higher_delta);

    static bool rangeCondition(unsigned char    , unsigned char candidate,
                               const int lower_value, const int higher_value);

	static const unsigned char plus_se_data[];
	static const StructuralElement plus_se;
	const static unsigned char X = Image::CHANNEL_MAX_VALUE;
};

} // core
} // imgproc

#endif // SEGMENTATION_UTILS_HPP_
