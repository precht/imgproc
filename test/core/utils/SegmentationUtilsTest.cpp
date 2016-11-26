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
    SU::regionGrowing(image3, 1, 1, plus_se, alwaysFalse, -1111, 2222);
    unsigned char expected[9]{}; // 0 filled array
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(full_region_growing)
{
    SU::regionGrowing(image3, 1, 1, plus_se, alwaysTrue, -1111, 2222);
    BOOST_CHECK(checkEqual(data3, image3));
}

BOOST_AUTO_TEST_CASE(invalid_seed_position)
{
    BOOST_CHECK_THROW(SU::regionGrowing(image3, -1, 0, plus_se, alwaysTrue, 0, 0), std::invalid_argument);
    BOOST_CHECK_THROW(SU::regionGrowing(image3, 0, -1, plus_se, alwaysTrue, 0, 0), std::invalid_argument);
    BOOST_CHECK_THROW(SU::regionGrowing(image3, 3, 0, plus_se, alwaysTrue, 0, 0), std::invalid_argument);
    BOOST_CHECK_THROW(SU::regionGrowing(image3, 0, 3, plus_se, alwaysTrue, 0, 0), std::invalid_argument);
}

// delta region growing

BOOST_AUTO_TEST_CASE(empty_lower_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 1, 1, plus_se, 9, 11);
    unsigned char expected[9]{}; // 0 filled array
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(empty_higher_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 0, 0, plus_se, 11, 9);
    unsigned char expected[9]{};
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(full_lower_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 1, 1, plus_se, 10, 0);
    BOOST_CHECK(checkEqual(data3, image3));
}

BOOST_AUTO_TEST_CASE(full_higher_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 0, 0, plus_se, 0, 10);
    BOOST_CHECK(checkEqual(data3, image3));
}

BOOST_AUTO_TEST_CASE(part_lower_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 2, 2, plus_se, 11, 9);
    unsigned char expected[]{
        10, 20, 30,
         0,  0, 40,
         0,  0, 50
    };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_higher_delta_region_growing)
{
    SU::deltaRegionGrowing(image3, 2, 2, plus_se, 9, 11);
    unsigned char expected[]{
         0,  0,  0,
        80, 90,  0,
        70, 60, 50
    };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(invalid_delta_region_growing)
{
    // delta cannot be negative
    // delta should be checked in deltaCondition function
    BOOST_CHECK_THROW(SU::deltaRegionGrowing(image3, 2, 2, plus_se, -1, 0), std::invalid_argument);
    BOOST_CHECK_THROW(SU::deltaRegionGrowing(image3, 2, 2, plus_se, 0, -1), std::invalid_argument);
}

// range region growing

BOOST_AUTO_TEST_CASE(empty_zero_zero_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 2, 2, plus_se, 0, 0);
    unsigned char expected[9]{};
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(full_from_zero_range_test_case)
{
    SU::rangeRegionGrowing(image3, 0, 0, plus_se, 0, 255);
    BOOST_CHECK(checkEqual(data3, image3));
}

BOOST_AUTO_TEST_CASE(full_from_negative_range_test_case)
{
    // should also work for negative starting range
    SU::rangeRegionGrowing(image3, 0, 0, plus_se, -9, 255);
    SU::rangeRegionGrowing(image3, 0, 0, plus_se, -11, 255);
    BOOST_CHECK(checkEqual(data3, image3));
}

BOOST_AUTO_TEST_CASE(empty_from_lower_range_region_growing)
{
    // image(0, 0, 1) is 10, not within 11...255
    SU::rangeRegionGrowing(image3, 0, 0, plus_se, 11, 255);
    unsigned char expected[9]{};
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(empty_to_higher_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 1, 1, plus_se, 0, 89);
    unsigned char expected[9]{};
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_from_lower_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 2, 0, plus_se, 11, 255);
    unsigned char expected[9]{
         0,  20,  30,
        80,  90,  40,
        70,  60,  50
     };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_to_higher_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 0, 2, plus_se, 0, 89);
    unsigned char expected[9]{
        10,  20,  30,
        80,   0,  40,
        70,  60,  50
     };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_CASE(part_from_lower_to_higher_range_region_growing)
{
    SU::rangeRegionGrowing(image3, 2, 2, plus_se, 30, 70);
    unsigned char expected[9]{
         0,   0,  30,
         0,   0,  40,
        70,  60,  50
     };
    BOOST_CHECK(checkEqual(expected, image3));
}

BOOST_AUTO_TEST_SUITE_END()

} // test
} // imgproc
