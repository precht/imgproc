/**
 *      Purpose:    Fixture class for utils tests
 *      Created:    13th Nov 2016
 *      Author:     Jakub Precht
 */

#ifndef IMAGE_FIXTURE_HPP_
#define IMAGE_FIXTURE_HPP_

#include "core/Image.hpp"

#include <vector>

namespace imgproc
{
namespace test
{

struct DataSet
{
    core::Image& image;
    const int x;
    const int y;
    const int ch;
    const int size = x * y * ch;

    DataSet( imgproc::core::Image &aImage, int aX, int aY, int aCh );
    virtual ~DataSet() = default;
};

class ImageFixture
{
public:
    std::vector<DataSet> data_sets_;

    static const int x0 = 2;
    static const int y0 = 2;
    static const int ch0 = 1;
    static const int size0 = x0 * y0 * ch0;
    static const int x1 = 2;
    static const int y1 = 2;
    static const int ch1 = 1;
    static const int size1 = x1 * y1 * ch1;
    static const int x2 = 4;
    static const int y2 = 3;
    static const int ch2 = 3;
    static const int size2 = x2 * y2 * ch2;
    static const unsigned char data0[];
    static const unsigned char data1[];
    static const unsigned char data2[];

    core::Image image0;
    core::Image image1;
    core::Image image2;

    ImageFixture();
    bool checkEqual(const unsigned char* data, int index, bool use_test_check = false);
    bool checkEqual(const unsigned char* data, core::Image& img, int x, int y, int ch, bool use_test_check = false);
    virtual ~ImageFixture() = default;
};

} // test
} // imgproc
#endif // IMAGE_FIXTURE_HPP_
