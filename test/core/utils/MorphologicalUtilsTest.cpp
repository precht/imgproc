/**
 *      Created:    24th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"
#include "test/ImageFixture.hpp"
#include "core/utils/MorphologicalUtils.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <string>

namespace imgproc
{
namespace test
{

using imgproc::core::Image;
using imgproc::core::StructuralElement;
using imgproc::core::MorphologicalUtils;

BOOST_FIXTURE_TEST_SUITE(MorphologicalUtilsTests, ImageFixture)

BOOST_AUTO_TEST_CASE(dummy)
{
    unsigned char expected[] { 0, 255, 0, 255, 255, 255, 0, 255, 0 };
    BOOST_CHECK(checkEqual(expected, plus_se, 3, 3, 1));
}

BOOST_AUTO_TEST_CASE(erosion)
{
    MorphologicalUtils::erosion(image2, plus_se);
    unsigned char expected[] {
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0, 255, 255,   0,   0,
        0,   0,   0,   0,   0, 255,   0,   0,
        0,   0,   0,   0,   0, 255,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0
    };
    BOOST_CHECK(checkEqual(expected, 2));

    // default structural element should also be plus
    Image img(data2, x2, y2, ch2);
    MorphologicalUtils::erosion(img);
    BOOST_CHECK(checkEqual(expected, 2));
}

BOOST_AUTO_TEST_CASE(dilation)
{
    MorphologicalUtils::dilation(image2, plus_se);
    unsigned char expected[] {
          0,   0,   0,   0, 255, 255,   0,   0,
          0, 255, 255, 255, 255, 255, 255,   0,
        255, 255, 255, 255, 255, 255, 255, 255,
          0, 255, 255, 255, 255, 255, 255, 255,
          0,   0, 255, 255, 255, 255, 255, 255,
          0,   0, 255, 255, 255, 255, 255,   0,
          0, 255, 255, 255, 255, 255, 255,   0,
          0,   0, 255, 255, 255, 255,   0,   0,
          0,   0,   0,   0, 255,   0,   0,   0
    };
    BOOST_CHECK(checkEqual(expected, 2));

    // default structural element should also be plus
    Image img(data2, x2, y2, ch2);
    MorphologicalUtils::dilation(img);
    BOOST_CHECK(checkEqual(expected, img, x2, y2, ch2));
}

BOOST_AUTO_TEST_CASE(opening)
{
    MorphologicalUtils::opening(image2, plus_se);
    unsigned char expected[] {
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0, 255, 255,   0,   0,
        0,   0,   0, 255, 255, 255, 255,   0,
        0,   0,   0,   0, 255, 255, 255,   0,
        0,   0,   0,   0, 255, 255, 255,   0,
        0,   0,   0,   0,   0, 255,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0
    };
    BOOST_CHECK(checkEqual(expected, 2));

    // default structural element should also be plus
    Image img(data2, x2, y2, ch2);
    MorphologicalUtils::opening(img);
    BOOST_CHECK(checkEqual(expected, img, x2, y2, ch2));
}

BOOST_AUTO_TEST_CASE(closing)
{
    MorphologicalUtils::closing(image2, plus_se);
    unsigned char expected[] {
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0, 255, 255,   0,   0,
        0, 255, 255, 255, 255, 255, 255,   0,
        0,   0, 255, 255, 255, 255, 255,   0,
        0,   0,   0, 255, 255, 255, 255,   0,
        0,   0,   0, 255, 255, 255,   0,   0,
        0,   0, 255, 255, 255, 255,   0,   0,
        0,   0,   0,   0, 255,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0
    };
    BOOST_CHECK(checkEqual(expected, 2));

    // default structural element should also be plus
    Image img(data2, x2, y2, ch2);
    MorphologicalUtils::closing(img);
    BOOST_CHECK(checkEqual(expected, img, x2, y2, ch2));
}

BOOST_AUTO_TEST_CASE(hmt)
{
    unsigned char hit_data[] {
          0, 255,   0,
          0, 255,   0,
        255, 255,   0
    };
    unsigned char miss_data[] {
          0,   0,   0,
        255,   0,   0,
          0,   0,   0
    };
    const StructuralElement hit(hit_data, 3, 3, 2, 1);
    const StructuralElement miss(miss_data, 3, 3, 2, 1);
    MorphologicalUtils::hmt(image2, hit, miss);
    unsigned char expected[] {
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0, 255,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0, 255,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0
    };
    BOOST_CHECK(checkEqual(expected, 2));
}

BOOST_AUTO_TEST_SUITE_END()

} // test
} // imgproc
