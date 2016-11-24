/**
 *      Created:    20th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "opencv/OpenCVImageHelper.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <string>

namespace imgproc
{
namespace test
{

using imgproc::core::Image;
using imgproc::opencv::OpenCVImageHelper;

BOOST_AUTO_TEST_SUITE(OpenCVImageHelperTests)

BOOST_AUTO_TEST_CASE(save_load_1_channel)
{
    const int a = 22;
    const int b = 25;
    const int c = 1;
    unsigned char data[a * b * c];
    for(int i = 0; i < a * b * c; ++i) data[i] = i % 255;
    std::string name = "a_test_data.bmp";
    std::shared_ptr<OpenCVImageHelper> helper(new OpenCVImageHelper);
    Image img1(data, a, b, c, helper, name, name);

    BOOST_CHECK(img1.save());
    Image img2(helper, name, name);

    BOOST_CHECK(img2.load());
    for(int i = 0; i < a * b * c; ++i)
        BOOST_CHECK_EQUAL(img2(i), img1(i));

    boost::filesystem::remove(name);
}

BOOST_AUTO_TEST_CASE(save_load_3_channel)
{
    const int a = 15;
    const int b = 12;
    const int c = 3;
    const int shift = 80;
    unsigned char data[a * b * c];
    for(int i = 0; i < a * b * c; ++i) data[i] = (i + (i % c) * shift) % 255;
    std::string name = "a_test_data.bmp";
    std::shared_ptr<OpenCVImageHelper> helper(new OpenCVImageHelper);
    Image img1(data, a, b, c, helper, name, name);

    BOOST_CHECK(img1.save());
    Image img2(helper, name, name);

    BOOST_CHECK(img2.load());
    for(int i = 0; i < a * b * c; ++i)
        BOOST_CHECK_EQUAL(img2(i), img1(i));

    boost::filesystem::remove(name);
}

BOOST_AUTO_TEST_SUITE_END()

} // test
} // imgproc
