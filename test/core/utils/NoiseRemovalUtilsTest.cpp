/**
 *      Purpose:    Tests for NoiseRemovalUtils (geometric mean filter and alpha trimmed mean filter)
 *      Created:    16th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "core/utils/NoiseRemovalUtils.hpp"
#include "test/ImageFixture.hpp"

#include <boost/test/unit_test.hpp>

//#include <iostream>

namespace imgproc
{
namespace test
{

using core::Image;
using core::NoiseRemovalUtils;

BOOST_FIXTURE_TEST_SUITE(NoiseRemovalUtilsTests, ImageFixture)

//    data0[] { 74, 89, 111, 102 };
//    data1[] { 0, 254, 255, 1 };

BOOST_AUTO_TEST_CASE(geometricMeanFilter)
{
    NoiseRemovalUtils::geometricMeanFilter(image0);
    unsigned char aa[] { 87, 90, 97, 97 };
    BOOST_CHECK(checkEqual(aa, 0));

    NoiseRemovalUtils::geometricMeanFilter(image1);
    unsigned char bb[] { 0, 0, 0, 0 };
    BOOST_CHECK(checkEqual(bb, 1));
}

BOOST_AUTO_TEST_CASE(alphaTrimmedMeanFilter_alpha_zero)
{
    NoiseRemovalUtils::alphaTrimmedMeanFilter(image0, 0);
    unsigned char aa[] { 88, 91, 98, 98 };
    BOOST_CHECK(checkEqual(aa, 0));

    NoiseRemovalUtils::alphaTrimmedMeanFilter(image1, 0);
    unsigned char bb[] { 113, 141, 141, 113 };
    BOOST_CHECK(checkEqual(bb, 1));
}
BOOST_AUTO_TEST_CASE(alphaTrimmedMeanFilter_alpha_one)
{
    NoiseRemovalUtils::alphaTrimmedMeanFilter(image0, 1);
    unsigned char aa[] { 87, 90, 100, 99 };
    BOOST_CHECK(checkEqual(aa, 0));

    NoiseRemovalUtils::alphaTrimmedMeanFilter(image1, 1);
    unsigned char bb[] { 109, 145, 145, 109 };
    BOOST_CHECK(checkEqual(bb, 1));
}
BOOST_AUTO_TEST_CASE(alphaTrimmedMeanFilter_alpha_two)
{
    NoiseRemovalUtils::alphaTrimmedMeanFilter(image0, 2);
    unsigned char aa[] { 85, 91, 103, 99 };
    BOOST_CHECK(checkEqual(aa, 0));

    NoiseRemovalUtils::alphaTrimmedMeanFilter(image1, 2);
    unsigned char bb[] { 101, 152, 153, 102 };
    BOOST_CHECK(checkEqual(bb, 1));
}
BOOST_AUTO_TEST_CASE(alphaTrimmedMeanFilter_alpha_three)
{
    NoiseRemovalUtils::alphaTrimmedMeanFilter(image0, 3);
    unsigned char aa[] { 84, 89, 105, 102 };
    BOOST_CHECK(checkEqual(aa, 0));

    NoiseRemovalUtils::alphaTrimmedMeanFilter(image1, 3);
    unsigned char bb[] { 85, 169, 170, 85 };
    BOOST_CHECK(checkEqual(bb, 1));
}
BOOST_AUTO_TEST_CASE(alphaTrimmedMeanFilter_alpha_four)
{
    NoiseRemovalUtils::alphaTrimmedMeanFilter(image0, 4);
    unsigned char aa[] { 89, 89, 102, 102 };
    BOOST_CHECK(checkEqual(aa, 0));

    NoiseRemovalUtils::alphaTrimmedMeanFilter(image1, 4);
    unsigned char bb[] { 1, 254, 254, 1 };
    BOOST_CHECK(checkEqual(bb, 1));
}

BOOST_AUTO_TEST_SUITE_END()

} // core
} // imgproc

