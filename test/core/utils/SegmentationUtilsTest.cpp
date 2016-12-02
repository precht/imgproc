/**
 *      Created:    24th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"
#include "test/ImageFixture.hpp"
#include "core/utils/SegmentationUtils.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <stdexcept>
#include <iostream>
#include <string>

namespace imgproc
{
namespace test
{

using imgproc::core::Image;
using imgproc::core::StructuralElement;
using imgproc::core::SegmentationUtils;
using imgproc::test::ImageFixture;

using SU = imgproc::core::SegmentationUtils;

using std::cout;
using std::endl;

BOOST_FIXTURE_TEST_SUITE(SegmentationUtilsTests, ImageFixture)

// data3, image3 used in tests:
// {
//    10,  20,  30,
//    80,  90,  40,
//    70,  60,  50
// };

// general region growing

bool alwaysTrue(unsigned char, unsigned char, int, int) { return true; }
bool alwaysFalse(unsigned char, unsigned char, int, int) { return false; }

BOOST_AUTO_TEST_CASE(empty_region_growing)
{
    SU::regionGrowing(image3, 1, 1, alwaysFalse, -1111, 2222, plus_se);
    unsigned char expected[9]{}; // 0 filled array
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(full_region_growing)
{
    SU::regionGrowing(image3, 1, 1, alwaysTrue, -1111, 2222, plus_se);
    unsigned char expected[9];
    std::fill_n(expected, 9, 255);
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(invalid_seed_position)
{
    BOOST_CHECK_THROW(SU::regionGrowing(image3, -1, 0, alwaysTrue, 0, 0, plus_se), std::invalid_argument);
    BOOST_CHECK_THROW(SU::regionGrowing(image3, 0, -1, alwaysTrue, 0, 0, plus_se), std::invalid_argument);
    BOOST_CHECK_THROW(SU::regionGrowing(image3, 3, 0, alwaysTrue, 0, 0, plus_se), std::invalid_argument);
    BOOST_CHECK_THROW(SU::regionGrowing(image3, 0, 3, alwaysTrue, 0, 0, plus_se), std::invalid_argument);
}

//// delta region growing

BOOST_AUTO_TEST_CASE(empty_lower_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 1, 1, 9, 11, plus_se);
    unsigned char expected[9]{
          0,   0,   0,
          0, 255,   0,
          0,   0,   0
    };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(empty_higher_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 0, 0, 11, 9, plus_se);
    unsigned char expected[9]{
        255,   0,   0,
          0,   0,   0,
          0,   0,   0
    };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(full_lower_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 1, 1, 10, 0, plus_se);
    unsigned char expected[9];
    std::fill_n(expected, 9, 255);
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(full_higher_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 0, 0, 0, 10, plus_se);
    unsigned char expected[9];
    std::fill_n(expected, 9, 255);
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_lower_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 2, 2, 11, 9, plus_se);
    unsigned char expected[]{
        255, 255, 255,
          0,   0, 255,
          0,   0, 255
    };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_higher_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 2, 2, 9, 11, plus_se);
    unsigned char expected[]{
          0,   0,   0,
        255, 255,   0,
        255, 255, 255
    };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(invalid_delta_region_growing)
{
    // delta cannot be negative
    // delta should be checked in deltaCondition function
    BOOST_CHECK_THROW(SU::deltaRegionGrowing(image3, 2, 2, -1, 0, plus_se), std::invalid_argument);
    BOOST_CHECK_THROW(SU::deltaRegionGrowing(image3, 2, 2, 0, -1, plus_se), std::invalid_argument);
}

// range region growing

BOOST_AUTO_TEST_CASE(empty_zero_zero_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 2, 2, 0, 0, plus_se);
    unsigned char expected[9]{};
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(full_from_zero_range_test_case)
{
    SU::rangeRegionGrowing(image3, 0, 0, 0, 255, plus_se);
    unsigned char expected[9];
    std::fill_n(expected, 9, 255);
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(full_from_negative_range_test_case)
{
    // should also work for negative starting range
    SU::rangeRegionGrowing(image3, 0, 0, -1, 255, plus_se);
    unsigned char expected[9];
    std::fill_n(expected, 9, 255);
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(empty_from_lower_range_region_growing)
{
    // image(0, 0, 1) is 10, not within 11...255
    SU::rangeRegionGrowing(image3, 0, 0, 11, 255, plus_se);
    unsigned char expected[9]{};
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(empty_to_higher_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 1, 1, 0, 89, plus_se);
    unsigned char expected[9]{};
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_from_lower_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 2, 0, 11, 255, plus_se);
    unsigned char expected[9]{
          0,  255,  255,
        255,  255,  255,
        255,  255,  255
     };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_to_higher_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 0, 2, 0, 89, plus_se);
    unsigned char expected[9]{
        255,  255,  255,
        255,    0,  255,
        255,  255,  255
     };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_from_lower_to_higher_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 2, 2, 30, 70, plus_se);
    unsigned char expected[9]{
          0,    0,  255,
          0,    0,  255,
        255,  255,  255
     };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_SUITE_END()

} // test
} // imgproc
