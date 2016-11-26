/**
 *      Created:    13th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "test/ImageFixture.hpp"

#include <boost/test/unit_test.hpp>

#include <vector>
#include <algorithm>

namespace imgproc
{
namespace test
{

using namespace boost::unit_test;
using imgproc::core::Image;

DataSet::DataSet(Image& aImage, int aX, int aY, int aCh)
    : image(aImage)
    , x(aX)
    , y(aY)
    , ch(aCh)
{ }

ImageFixture::ImageFixture()
    : image0(data0, x0, y0, ch0)
    , image1(data1, x1, y1, ch1)
    , image2(data2, x2, y2, ch2)
    , image3(data3, x3, y3, ch3)
    , plus_se(plus_se_data, plus_se_x, plus_se_y, plus_se_origin_x, plus_se_origin_y)
{
    data_sets_.push_back(DataSet(image0, x0, y0, ch0));
    data_sets_.push_back(DataSet(image1, x1, y1, ch1));
    data_sets_.push_back(DataSet(image2, x2, y2, ch2));
    data_sets_.push_back(DataSet(image3, x3, y3, ch3));
}

bool ImageFixture::checkEqual(const unsigned char* data, int index, bool use_test_check)
{
    return checkEqual(data, data_sets_[index].image, data_sets_[index].x, data_sets_[index].y,
                      data_sets_[index].ch, use_test_check);
}

bool ImageFixture::checkEqual(const unsigned char* data, const core::Image& img, bool use_test_check)
{
    const int x = img.rows();
    const int y = img.columns();
    const int ch = img.channels();
    bool is_correct = true;
    for(int i = 0; i < x; ++i)
        for(int j = 0; j < y; ++j)
            for(int k = 0; k < ch; ++k)
            {
                is_correct &= data[(i * y * ch) + (j * ch) + k] == img.at(i, j, k);
                if (use_test_check) BOOST_CHECK_EQUAL(data[(i * y * ch) + (j * ch) + k], img.at(i, j, k));
            }

    return is_correct;
}

bool ImageFixture::checkEqual(const unsigned char* data, const Image& img, int x, int y, int ch, bool use_test_check)
{
    bool is_correct = true;
    for(int i = 0; i < x; ++i)
        for(int j = 0; j < y; ++j)
            for(int k = 0; k < ch; ++k)
            {
                is_correct &= data[(i * y * ch) + (j * ch) + k] == img.at(i, j, k);
                if (use_test_check) BOOST_CHECK_EQUAL(data[(i * y * ch) + (j * ch) + k], img.at(i, j, k));
            }

    return is_correct;
}

const unsigned char ImageFixture::data0[] = {
    74,    89,
   111,   102
};

const unsigned char ImageFixture::data1[] = {
     0,   254,
   255,     1
};

// bitwise image for morphological tests
const unsigned char ImageFixture::data2[] {
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0, 255, 255,   0,   0,
    0, 255, 255, 255, 255, 255, 255,   0,
    0,   0,   0,   0, 255, 255, 255,   0,
    0,   0,   0, 255, 255, 255, 255,   0,
    0,   0,   0, 255,   0, 255,   0,   0,
    0,   0, 255, 255,   0, 255,   0,   0,
    0,   0,   0,   0, 255,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0
};

const unsigned char ImageFixture::data3[] {
    10,  20,  30,
    80,  90,  40,
    70,  60,  50
};

const unsigned char ImageFixture::plus_se_data[] {
      0, 255,   0,
    255, 255, 255,
      0, 255,   0
};


} // test
} // imgproc
