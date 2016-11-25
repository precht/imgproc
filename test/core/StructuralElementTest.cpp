/**
 *      Created:    24th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"

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

BOOST_AUTO_TEST_SUITE(StructuralElementTest)

BOOST_AUTO_TEST_CASE(dummy)
{
    StructuralElement();
}

BOOST_AUTO_TEST_CASE(constructor_without_data)
{
    StructuralElement s1;
    BOOST_CHECK_EQUAL(s1.rows(), 0);
    BOOST_CHECK_EQUAL(s1.columns(), 0);
    BOOST_CHECK_EQUAL(s1.getOriginRow(), 0);
    BOOST_CHECK_EQUAL(s1.getOriginColumn(), 0);

    StructuralElement s2(10, 20, 4, 7);
    BOOST_CHECK_EQUAL(s2.rows(), 10);
    BOOST_CHECK_EQUAL(s2.columns(), 20);
    BOOST_CHECK_EQUAL(s2.channels(), 1);
    BOOST_CHECK_EQUAL(s2.getOriginRow(), 4);
    BOOST_CHECK_EQUAL(s2.getOriginColumn(), 7);
}

BOOST_AUTO_TEST_CASE(constructor_with_data)
{
    unsigned char data[] { 0, 1, 2, 3, 4, 5 };
    StructuralElement s1(data, 2, 3, 1, 2);
    BOOST_CHECK_EQUAL(s1.rows(), 2);
    BOOST_CHECK_EQUAL(s1.columns(), 3);
    BOOST_CHECK_EQUAL(s1.channels(), 1);
    BOOST_CHECK_EQUAL(s1.getOriginRow(), 1);
    BOOST_CHECK_EQUAL(s1.getOriginColumn(), 2);
    for(int i = 0; i < 6; i++) BOOST_CHECK_EQUAL(s1(i), i);
}

BOOST_AUTO_TEST_CASE(invalid_constructor)
{
    BOOST_CHECK_THROW(StructuralElement(0, 0, 1, 0), std::invalid_argument);
    BOOST_CHECK_THROW(StructuralElement(0, 0, 0, 1), std::invalid_argument);
    BOOST_CHECK_THROW(StructuralElement(2, 3, -1, 0), std::invalid_argument);
    BOOST_CHECK_THROW(StructuralElement(2, 3, 0, -1), std::invalid_argument);
    unsigned char data[] { 0, 1, 2, 3, 4, 5 };
    BOOST_CHECK_THROW(StructuralElement(data, 0, 0, 1, 0), std::invalid_argument);
    BOOST_CHECK_THROW(StructuralElement(data, 0, 0, 0, 1), std::invalid_argument);
    BOOST_CHECK_THROW(StructuralElement(data, 2, 3, -1, 0), std::invalid_argument);
    BOOST_CHECK_THROW(StructuralElement(data, 2, 3, 0, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(correct_set_origin)
{
        StructuralElement s1(10, 10, 0, 0);
        s1.setOriginRow(8);
        s1.setOriginColumn(3);
        BOOST_CHECK_EQUAL(s1.getOriginRow(), 8);
        BOOST_CHECK_EQUAL(s1.getOriginColumn(), 3);
}

BOOST_AUTO_TEST_CASE(invalid_set_origin)
{
        StructuralElement s1(10, 10, 0, 0);
        BOOST_CHECK_THROW(s1.setOriginRow(-1), std::invalid_argument);
        BOOST_CHECK_THROW(s1.setOriginRow(11), std::invalid_argument);
        BOOST_CHECK_THROW(s1.setOriginRow(10), std::invalid_argument);
        BOOST_CHECK_THROW(s1.setOriginColumn(-1), std::invalid_argument);
        BOOST_CHECK_THROW(s1.setOriginColumn(11), std::invalid_argument);
        BOOST_CHECK_THROW(s1.setOriginColumn(10), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

} // test
} // imgproc
