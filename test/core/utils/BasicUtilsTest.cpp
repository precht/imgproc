/**
 *      Purpose:    Tests for BasicUtils (changing brignthess, contrast and negation)
 *      Created:    16th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "core/utils/BasicUtils.hpp"
#include "test/ImageFixture.hpp"

#include <boost/test/unit_test.hpp>

//#include <iostream>

namespace imgproc
{
namespace test
{

using core::Image;
using core::BasicUtils;

BOOST_FIXTURE_TEST_SUITE(BasicUtilsTests, ImageFixture)

BOOST_AUTO_TEST_CASE(ImageFixture)
{
    BOOST_CHECK(checkEqual(data0, image0, x0, y0, ch0));
    unsigned char aa[] {74, 89, 111, 102};
    BOOST_CHECK(checkEqual(aa, 0));

    BOOST_CHECK(checkEqual(data1, image1, x1, y1, ch1));
    unsigned char bb[] {0, 254, 255, 1};
    BOOST_CHECK(checkEqual(bb, 1));
}

BOOST_AUTO_TEST_CASE(brightness)
{
    BasicUtils::brightness(image0, 150);
    unsigned char aa[] {224, 239, 255, 252};
    BOOST_REQUIRE(checkEqual(aa, 0));

    BasicUtils::brightness(image0, -225);
    unsigned char bb[] {0, 14, 30, 27};
    BOOST_CHECK(checkEqual(bb, 0));
}

BOOST_AUTO_TEST_CASE(negation)
{
    BasicUtils::negate(image0);
    unsigned char aa[] {181, 166, 144, 153};
    BOOST_CHECK(checkEqual(aa, 0));

    BasicUtils::negate(image1);
    unsigned char bb[] {255, 1, 0, 254};
    BOOST_CHECK(checkEqual(bb, 1));
}

BOOST_AUTO_TEST_CASE(contrast_minus_1_twice)
{
    BasicUtils::contrast(image0, 1.0);
    BOOST_CHECK(checkEqual(data0, 0));
    BasicUtils::contrast(image0, -1.0);
    BasicUtils::contrast(image0, -1.0);
    BOOST_CHECK(checkEqual(data0, 0));

    BasicUtils::contrast(image1, 1.0);
    BOOST_CHECK(checkEqual(data1, 1));
    BasicUtils::contrast(image1, -1.0);
    BasicUtils::contrast(image1, -1.0);
    BOOST_CHECK(checkEqual(data1, 1));
}

BOOST_AUTO_TEST_CASE(contrast_twice_then_half)
{
    BasicUtils::contrast(image0, 2.0);
    unsigned char aa[] {21, 51, 95, 77};
    BOOST_CHECK(checkEqual(aa, 0));
    BasicUtils::contrast(image0, 0.5);
    BOOST_CHECK(checkEqual(data0, 0));
}

BOOST_AUTO_TEST_CASE(contrast_minus_1_once)
{
    BasicUtils::contrast(image0, -1.0);
    unsigned char aa[] {181, 166, 144, 153};
    BOOST_CHECK(checkEqual(aa, 0));

    BasicUtils::contrast(image1, -1.0);
    unsigned char bb[] {255, 1, 0, 254};
    BOOST_CHECK(checkEqual(bb, 1));
}

BOOST_AUTO_TEST_SUITE_END()

} // test
} // imgproc



