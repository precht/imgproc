/**
 *      Purpose:
 *          This class tests following utils:
 *          - basic
 *          - geometric
 *          - noise removal
 *          - error measure.
 *
 *      Created:    27th Oct 2016
 *      Author(s):  Jakub Precht
 */

#include "img/ImageCV.hpp"
#include "img/utils.hpp"

#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>

using namespace imgprocapp;
using namespace imgprocapp::img::utils;
using img::byte;
using img::ImageCV;
using std::cout;
using std::endl;

// fixture class and data
class ImageF : public ::testing::Test
{
protected:
    static const int x1 = 3;
    static const int x2 = 4;
    static const int y1 = 2;
    static const int y2 = 3;
    static const int ch1 = 1;
    static const int ch2 = 3;
    static const int size1 = x1 * y1 * ch1;
    static const int size2 = x2 * y2 * ch2;
    static const byte data1[];
    static const byte data2[];

    ImageCV image1;
    ImageCV image2;

    ImageF()
        : image1(x1, y1, ch1, data1_copy)
        , image2(x2, y2, ch2, data2_copy)
    {
        std::copy(data1, data1 + size1, data1_copy);
        std::copy(data2, data2 + size2, data2_copy);
    }

    virtual ~ImageF() { }

    static bool check_if_different(int x, int y, int ch, const byte *data, ImageCV &A, bool use_expect_eq = false)
    {
        bool sth_wrong = false;
        for(int i = 0; i < x; ++i)
            for(int j = 0; j < y; ++j)
                for(int k = 0; k < ch; ++k)
                {
                    sth_wrong |= (data[(i * y * ch) + (j * ch) + k] != *A.ptr(i, j, k));
                    if(use_expect_eq) EXPECT_EQ(data[(i * y * ch) + (j * ch) + k], *A.ptr(i, j, k));
                }

        return sth_wrong;
    }

private:
    byte data1_copy[size1];
    byte data2_copy[size2];


};


const byte ImageF::data1[] = {
    74,    128,
     0,    197,
    31,    255
};

const byte ImageF::data2[] {
    20,  38,  15,    204, 181,  74,     93, 241,  63,
    89,  58, 172,    138,  58, 235,    195,   0,  51,
   179, 255, 157,     45, 103, 231,     18,  16,   0,
   138,  48,  61,    246,   1,  73,    158,  92, 173
};



// Initial Fixture SetUp
TEST_F(ImageF, fixtureSetUpTest1)
{
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data1, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, fixtureSetUpTest2)
{
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data2, image2));
//    cout << image2 << endl;
}

/*
// Brightness
TEST_F(ImageF, brightnessTest1_1)
{
    BasicUtils::change_brightness(&image1, 100);
    byte data[] {
        174,    228,
        100,    255,
        131,    255
    };
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, brightnessTest1_2)
{
    BasicUtils::change_brightness(&image1, -100);
    byte data[] {
        0,     28,
        0,     97,
        0,    155
    };
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, brightnessTest2_1)
{
    BasicUtils::change_brightness(&image2, 100);
    byte data[] {
        120, 138, 115,    255, 255, 174,    193, 255, 163,
        189, 158, 255,    238, 158, 255,    255, 100, 151,
        255, 255, 255,    145, 203, 255,    118, 116, 100,
        238, 148, 161,    255, 101, 173,    255, 192, 255
    };
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data, image2));
//    cout << image2 << endl;
}
TEST_F(ImageF, brightnessTest2_2)
{
    BasicUtils::change_brightness(&image2, -100);
    byte data[] {
        0,   0,   0,    104,  81,   0,      0, 141,   0,
        0,   0,  72,     38,   0, 135,     95,   0,   0,
       79, 155,  57,      0,   3, 131,      0,   0,   0,
       38,   0,   0,    146,   0,   0,     58,   0,  73
    };
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data, image2));
//    cout << image2 << endl;
}

// Negation
TEST_F(ImageF, negateTest1)
{
    BasicUtils::negate(&image1);
    byte data[] {
        181,    127,
        255,     58,
        224,      0
    };
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, negateTest2)
{
    BasicUtils::negate(&image2);
    byte data[] {
        235, 217, 240,     51,  74, 181,    162,  14, 192,
        166, 197,  83,    117, 197,  20,     60, 255, 204,
         76,   0,  98,    210, 152,  24,    237, 239, 255,
        117, 207, 194,      9, 254, 182,     97, 163,  82
    };
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data, image2));
//    cout << image2 << endl;
}

// Contrast
TEST_F(ImageF, contrastTest1_1)
{
    BasicUtils::change_contrast(&image1, 2.1);
    byte data[] {
        15,    129,
         0,    255,
         0,    255
    };
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, contrastTest1_2)
{
    BasicUtils::change_contrast(&image1, -0.6);
    byte data[] {
        158,    126,
        203,     85,
        184,     50
    };
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, contrastTest2_1)
{
    BasicUtils::change_contrast(&image2, 2.6);
    byte data[] {
        0,   0,   0,    255, 255,   0,     38, 255,   0,
       28,   0, 243,    155,   0, 255,    255,   0,   0,
      255, 255, 204,      0,  64, 255,      0,   0,   0,
      155,   0,   0,    255,   0,   0,    207,  36, 246
    };
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data, image2));
//    cout << image2 << endl;
}
TEST_F(ImageF, contrastTest2_2)
{
    BasicUtils::change_contrast(&image2, -0.6);
    byte data[] {
        191, 180, 194,     80,  94, 158,    147,  58, 165,
        149, 168, 100,    120, 168,  62,     86, 203, 172,
         95,  50, 109,    176, 141,  64,    192, 193, 203,
        120, 174, 166,     55, 202, 159,    108, 148,  99
    };
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data, image2));
//    cout << image2 << endl;
}

// TODO: it looks like because i implemented all rotations using doubles, the rotations are not very precise

// Horizontal flip
TEST_F(ImageF, horizontalFlipTest1)
{
    GeometricUtils::flip_horizontally(&image1);
    byte data[] {
        128,   74,
        197,    0,
        255,   31
    };
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, horizontalFlipTest2)
{
    GeometricUtils::flip_horizontally(&image2);
    byte data[] {
        93, 241,  63,    204, 181,  74,     20,  38,  15,
       195,   0,  51,    138,  58, 235,     89,  58, 172,
        18,  16,   0,     45, 103, 231,    179, 255, 157,
       158,  92, 173,    246,   1,  73,    138,  48,  61
    };
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data, image2));
//    cout << image2 << endl;
}


// Vertical flip
TEST_F(ImageF, verticalFlipTest1)
{
    GeometricUtils::flip_vertically(&image1);
    byte data[] {
        31,    255,
         0,    197,
        74,    128
    };
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, verticalFlipTest2)
{
    GeometricUtils::flip_vertically(&image2);
    byte data[] {
        93, 241,  63,    204, 181,  74,     20,  38,  15,
       195,   0,  51,    138,  58, 235,     89,  58, 172,
        18,  16,   0,     45, 103, 231,    179, 255, 157,
       158,  92, 173,    246,   1,  73,    138,  48,  61
    };
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data, image2));
//    cout << image2 << endl;
}

// Diagonal flip
TEST_F(ImageF, diagonalFlipTest1)
{
    GeometricUtils::flip_vertically(&image1);
    byte data[] {
       255,    31,
       197,    0,
       128,    74
    };
    EXPECT_FALSE(check_if_different(x1, y1, ch1, data, image1));
//    cout << image1 << endl;
}
TEST_F(ImageF, diagonalFlipTest2)
{
    GeometricUtils::flip_vertically(&image2);
    byte data[] {
        158,  92, 173,    246,   1,  73,    138,  48,  61,
        18,  16,   0,      45, 103, 231,    179, 255, 157,
        195,   0,  51,    138,  58, 235,     89,  58, 172,
        93, 241,  63,     204, 181,  74,     20,  38,  15

    };
    EXPECT_FALSE(check_if_different(x2, y2, ch2, data, image2));
//    cout << image2 << endl;
}
*/







