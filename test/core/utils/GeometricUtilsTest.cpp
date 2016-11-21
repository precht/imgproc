/**
 *      Purpose:    Tests for Geometric Utils (horizontal, vertical, diagonal filps and scaling)
 *      Created:    16th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "core/utils/GeometricUtils.hpp"
#include "test/ImageFixture.hpp"

#include <boost/test/unit_test.hpp>
//#include <iostream>

namespace imgproc
{
namespace test
{

using core::Image;
using core::GeometricUtils;

BOOST_FIXTURE_TEST_SUITE(GeometricUtilsTests, ImageFixture)

//    data0[] { 74, 89, 111, 102 };
//    data1[] { 0, 254, 255, 1 };

BOOST_AUTO_TEST_CASE(horizontal_flip)
{
    GeometricUtils::horizontalFlip(image0);
    unsigned char aa[] { 89, 74, 102, 111 };
    BOOST_CHECK(checkEqual(aa, 0));
}

BOOST_AUTO_TEST_CASE(vertical_flip)
{
    GeometricUtils::verticalFlip(image0);
    unsigned char aa[] { 111, 102, 74, 89 };
    BOOST_CHECK(checkEqual(aa, 0));
}

BOOST_AUTO_TEST_CASE(diagonal_flip)
{
    GeometricUtils::diagonalFlip(image0);
    unsigned char aa[] { 102, 111, 89, 74 };
    BOOST_CHECK(checkEqual(aa, 0));
}

BOOST_AUTO_TEST_CASE(scale_twice)
{
    GeometricUtils::scale(image0, 2.0);
    unsigned char aa[] {
        74,     74,     89,     89,
        74,     74,     89,     89,
       111,    111,    102,    102,
       111,    111,    102,    102
    };
    BOOST_CHECK(checkEqual(aa, image0, 4, 4, 1));
}

BOOST_AUTO_TEST_CASE(scale_half)
{
    GeometricUtils::scale(image0, 0.5);
    unsigned char aa[] { 74 };
    BOOST_CHECK(checkEqual(aa, image0, 1, 1, 1));
}
BOOST_AUTO_TEST_CASE(scale_close_to_one_no_change)
{
    GeometricUtils::scale(image0, 1.1);
    BOOST_CHECK(checkEqual(data0, 0));
}
BOOST_AUTO_TEST_CASE(scale_one_and_half_should_change)
{
    GeometricUtils::scale(image0, 1.5);
    unsigned char aa[] {
        74,     74,     89,
        74,     74,     89,
       111,    111,    102
    };
    BOOST_CHECK(checkEqual(aa, image0, 3, 3, 1));
}

BOOST_AUTO_TEST_SUITE_END()

} // test
} // imgproc



