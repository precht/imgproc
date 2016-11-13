
#include "test/ImageFixture.hpp"
#include "img/utils.hpp"

#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <iostream>


using namespace boost::unit_test;
using namespace imgprocapp;
using namespace imgprocapp::img;
using img::byte;
using img::ImageCV;
using std::cout;
using std::endl;

Image_F::Image_F()
    : image1(x1, y1, ch1, data1_copy)
    , image2(x2, y2, ch2, data2_copy)
    , image3(x3, y3, ch3, data3_copy)
{
    std::copy(data1, data1 + size1, data1_copy);
    std::copy(data2, data2 + size2, data2_copy);
    std::copy(data3, data3 + size3, data3_copy);
}

bool Image_F::check_if_different(ImageCV &A, const byte *data, int x, int y, int ch, bool use_test_check)
{
    bool sth_wrong = false;
    for(int i = 0; i < x; ++i)
        for(int j = 0; j < y; ++j)
            for(int k = 0; k < ch; ++k)
            {
                sth_wrong |= (data[(i * y * ch) + (j * ch) + k] != *A.ptr(i, j, k));
                if(use_test_check) BOOST_CHECK_EQUAL(data[(i * y * ch) + (j * ch) + k], *A.ptr(i, j, k));
            }

    return sth_wrong;
}

const byte Image_F::data1[] = {
    74,    89,
   111,   102
};

const byte Image_F::data2[] = {
    74,    128,
     0,    197,
    31,    255
};

const byte Image_F::data3[] {
    20,  38,  15,    204, 181,  74,     93, 241,  63,
    89,  58, 172,    138,  58, 235,    195,   0,  51,
   179, 255, 157,     45, 103, 231,     18,  16,   0,
   138,  48,  61,    246,   1,  73,    158,  92, 173
};
