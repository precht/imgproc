/**
 *      Created:    20th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"

#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>

#include <iostream>
#include <string>

using imgproc::core::Image;
using imgproc::core::ImageHelper;

BOOST_AUTO_TEST_SUITE(ImageTests)

BOOST_AUTO_TEST_CASE(dummy)
{
    Image a;
    Image b(0, 0, 0);
    Image c(nullptr, 0, 0, 0);
}

BOOST_AUTO_TEST_CASE(set_size)
{
    Image img(11, 22, 3);
    BOOST_CHECK_EQUAL(img.rows(), 11);
    BOOST_CHECK_EQUAL(img.columns(), 22);
    BOOST_CHECK_EQUAL(img.channels(), 3);
    BOOST_CHECK_EQUAL(img.size(), 11 * 22 * 3);
}

BOOST_AUTO_TEST_CASE(data_accessors)
{
    const int a = 4;
    const int b = 5;
    const int c = 3;
    const int size = a * b * c;
    Image img(a, b, c);
    for(unsigned char i = 0; i < size; i++) img(i) = i;
    for(unsigned char i = 0; i < size; i++) BOOST_CHECK_EQUAL(img(i), i);
    for(int x = 0; x < a; x++)
        for(int y = 0; y < b; y++)
            for(int z = 0; z < c; z++)
            {
                BOOST_CHECK_EQUAL(img(x, y, z), (x * b * c) + (y * c) + z);
                img(x, y, z) = size - (x * b * c) - (y * c) - z;
            }
    for(unsigned char i = 0; i < size; i++) BOOST_CHECK_EQUAL(img(i), size - i);
}

BOOST_AUTO_TEST_CASE(data_out_of_range)
{
    Image a;
    BOOST_CHECK_THROW(a(0), std::out_of_range);
    BOOST_CHECK_THROW(a(0, 0, 0), std::out_of_range);
    Image b(0, 0, 0);
    BOOST_CHECK_THROW(b(0), std::out_of_range);
    BOOST_CHECK_THROW(b(0, 0, 0), std::out_of_range);
    Image c(1, 1, 1);
    BOOST_CHECK_THROW(c(-1), std::out_of_range);
    BOOST_CHECK_THROW(c(1), std::out_of_range);
    BOOST_CHECK_THROW(c(-1, 0, 0), std::out_of_range);
    BOOST_CHECK_THROW(c(0, -1, 0), std::out_of_range);
    BOOST_CHECK_THROW(c(0, 0, -1), std::out_of_range);
    BOOST_CHECK_THROW(c(1, 0, 0), std::out_of_range);
    BOOST_CHECK_THROW(c(0, 1, 0), std::out_of_range);
    BOOST_CHECK_THROW(c(0, 0, 1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(set_data_in_constructor)
{
    for(int k = 1; k <= 4; k++)
    {
        const int a = 2;
        const int b = 1;
        const int c = k;
        const int size = a * b * c;
        unsigned char *data = new unsigned char[size];
        for(int i = 0; i < size; i++) data[i] = i;
        Image img(data, a, b, c);
        BOOST_CHECK_EQUAL(img.rows(), a);
        BOOST_CHECK_EQUAL(img.columns(), b);
        BOOST_CHECK_EQUAL(img.channels(), c);
        for(int i = 0; i < size; i++) BOOST_CHECK_EQUAL(img(i), i);
        for(int x = 0; x < a; x++)
            for(int y = 0; y < b; y++)
                for(int z = 0; z < c; z++)
                    BOOST_CHECK_EQUAL(img(x, y, z), (x * b * c) + (y * c) + z);
        delete[] data;
    }
}

BOOST_AUTO_TEST_CASE(copyable)
{
    unsigned char data[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    Image a1(data, 4, 1, 3);
    for(int i = 0; i < 12; i++) BOOST_CHECK_EQUAL(a1(i), i);
    Image a2(a1);
    for(int i = 0; i < 12; i++) BOOST_CHECK_EQUAL(a2(i), i);
    Image a3;
    a3 = a2;
    for(int i = 0; i < 12; i++) BOOST_CHECK_EQUAL(a3(i), i);
}

BOOST_AUTO_TEST_CASE(movable)
{
    unsigned char data[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    Image a1(data, 4, 1, 3);
    for(int i = 0; i < 12; i++) BOOST_CHECK_EQUAL(a1(i), i);
    Image a2(std::move(a1));
    for(int i = 0; i < 12; i++) BOOST_CHECK_EQUAL(a2(i), i);
    Image a3;
    a3 = std::move(a2);
    for(int i = 0; i < 12; i++) BOOST_CHECK_EQUAL(a3(i), i);
}

BOOST_AUTO_TEST_CASE(set_get_names)
{
    std::string in = "in_name.bmp";
    std::string out = "out_name.bmp";
    Image a(0, 0, 0);
    BOOST_CHECK_EQUAL(a.getInputName(), "");
    BOOST_CHECK_EQUAL(a.getOutputName(), "");
    a.setInputName(in);
    BOOST_CHECK_EQUAL(a.getInputName(), in);
    in = "";
    BOOST_CHECK(a.getInputName() != "");
    a.setOutputName(out);
    BOOST_CHECK_EQUAL(a.getOutputName(), out);
    out = "";
    BOOST_CHECK(a.getOutputName() != "");
}

BOOST_AUTO_TEST_CASE(crop)
{
    Image a(4, 5, 1);
    a.crop(1, 2, 0, 0);
    BOOST_CHECK_EQUAL(a.rows(), 1);
    a.crop(0, 0, 2, 1);
    BOOST_CHECK_EQUAL(a.columns(), 2);

    Image b(4, 5, 1);
    b.crop(1, 3, 0, 0);
    BOOST_CHECK_EQUAL(b.rows(), 0);
    b.crop(0, 0, 3, 2);
    BOOST_CHECK_EQUAL(b.columns(), 0);

    unsigned char data[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    Image c(data, 4, 3, 1);
    c.crop(1, 1, 0, 0);
    BOOST_CHECK_EQUAL(c.rows(), 2);
    for(int i = 0; i < 6; i++) BOOST_CHECK_EQUAL(c(i), i + 3);
    c.crop(0, 0, 1, 1);
    BOOST_CHECK_EQUAL(c(0), 4);
    BOOST_CHECK_EQUAL(c(1), 7);
    BOOST_CHECK_EQUAL(c.columns(), 1);
}

BOOST_AUTO_TEST_CASE(resize)
{
    Image a(10, 20, 3);
    a.resize(2, 3, 2);
    BOOST_CHECK_EQUAL(a.rows(), 2);
    BOOST_CHECK_EQUAL(a.columns(), 3);
    BOOST_CHECK_EQUAL(a.channels(), 2);
    BOOST_CHECK_EQUAL(a.size(), 12);

    unsigned char data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 11 };
    Image b(data, 3, 4, 1);
    b.resize(3, 3, 3);
    BOOST_CHECK_EQUAL(b.rows(), 3);
    BOOST_CHECK_EQUAL(b.columns(), 3);
    BOOST_CHECK_EQUAL(b.channels(), 3);
    BOOST_CHECK_EQUAL(b.size(), 27);
    for(int i = 0; i < 27; i++) BOOST_CHECK_EQUAL(b(i), 0);
}

BOOST_AUTO_TEST_CASE(clear)
{
    unsigned char data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 11 };
    Image a(data, 3, 4, 1);
    a.clear();
    BOOST_CHECK_EQUAL(a.rows(), 0);
    BOOST_CHECK_EQUAL(a.columns(), 0);
    BOOST_CHECK_EQUAL(a.channels(), 0);
}

BOOST_AUTO_TEST_CASE(invalid_argument_in_crop)
{
    Image a(4, 5, 1);
    BOOST_CHECK_THROW(a.crop(-1, 1, 1, 1), std::invalid_argument);
    BOOST_CHECK_THROW(a.crop(1, -1, 1, 1), std::invalid_argument);
    BOOST_CHECK_THROW(a.crop(1, 1, -1, 1), std::invalid_argument);
    BOOST_CHECK_THROW(a.crop(-1, 1, 1, -1), std::invalid_argument);
    BOOST_CHECK_THROW(a.crop(2, 3, 1, 1), std::invalid_argument);
    BOOST_CHECK_THROW(a.crop(1, 1, 3, 3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_argument_in_constructor)
{
    BOOST_CHECK_THROW(Image(-1, 0, 0), std::invalid_argument);
    BOOST_CHECK_THROW(Image(0, -1, 0), std::invalid_argument);
    BOOST_CHECK_THROW(Image(0, 0, -1), std::invalid_argument);
    BOOST_CHECK_THROW(Image(-1, 1, -1), std::invalid_argument);

    unsigned char data[] { 1 };
    BOOST_CHECK_THROW(Image(data, -1, 0, 0), std::invalid_argument);
    BOOST_CHECK_THROW(Image(data, 0, -1, 0), std::invalid_argument);
    BOOST_CHECK_THROW(Image(data, 0, 0, -1), std::invalid_argument);
    BOOST_CHECK_THROW(Image(data, -1, 1, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(load_save)
{
    MOCK_BASE_CLASS(MockedHelper, ImageHelper)
    {
        MOCK_METHOD(load, 1)
        MOCK_METHOD(save, 1)
    };

    std::shared_ptr<MockedHelper> helper(new MockedHelper);
    MOCK_EXPECT((*helper.get()).load).exactly(2).returns(true);
    MOCK_EXPECT((*helper.get()).save).exactly(2).returns(true);
    std::string in = "in_name.bmp";
    std::string out = "out_name.bmp";
    Image a(helper, in, out);
    a.load();
    a.save();
    std::string in2 = "this_is_in_2";
    std::string out2 = "this_is_out_2";
    a.load(in2);
    a.save(out2);
    BOOST_CHECK_EQUAL(a.getInputName(), in2);
    BOOST_CHECK_EQUAL(a.getOutputName(), out2);
}

BOOST_AUTO_TEST_CASE(logic_error_in_load_save)
{
    std::string in = "in_name.bmp";
    std::string out = "out_name.bmp";
    Image a(nullptr, in, out);
    BOOST_CHECK_THROW(a.load(), std::logic_error);
    BOOST_CHECK_THROW(a.load(in), std::logic_error);
    BOOST_CHECK_THROW(a.save(), std::logic_error);
    BOOST_CHECK_THROW(a.save(out), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()
