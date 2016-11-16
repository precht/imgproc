/**
 *      Purpose:    Tests for BasicUtils (changing brignthess, contrast and negation)
 *      Created:    16th Nov 2016
 *      Author:     Jakub Precht
 */

#include "img/ImageCV.hpp"
#include "img/utils/BasicUtils.hpp"
#include "test/ImageFixture.hpp"

#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace imgprocapp;
using namespace imgprocapp::img;
using namespace imgprocapp::img::utils;
using img::byte;
using img::ImageCV;
using std::cout;
using std::endl;

BOOST_FIXTURE_TEST_SUITE( BasicUtilsTests, ImageFixture )

BOOST_AUTO_TEST_CASE( ImageFixture )
{
    BOOST_CHECK( checkEqual( data0, image0, x0, y0, ch0 ) );
    byte aa[] { 74, 89, 111, 102 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    BOOST_CHECK( checkEqual( data1, image1, x1, y1, ch1 ) );
    byte bb[] { 0, 254, 255, 1 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
//    cout << image1 << endl;
}

BOOST_AUTO_TEST_CASE( brightness )
{
    BasicUtils::change_brightness( &image0, 150 );
    byte aa[] { 224, 239, 255, 252 };
    BOOST_REQUIRE( checkEqual( aa, 0 ) );

    BasicUtils::change_brightness( &image0, -225 );
    byte bb[] { 0, 14, 30, 27 };
    BOOST_CHECK( checkEqual( bb, 0 ) );
}

BOOST_AUTO_TEST_CASE( negation )
{
    BasicUtils::negate( &image0 );
    byte aa[] { 181, 166, 144, 153 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    BasicUtils::negate( &image1 );
    byte bb[] { 255, 1, 0, 254 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
}

BOOST_AUTO_TEST_CASE( contrast_1 )
{
    BasicUtils::change_contrast( &image0, 1.0 );
    BOOST_CHECK( checkEqual( data0, 0 ) );
    BasicUtils::change_contrast( &image0, -1.0 );
    BasicUtils::change_contrast( &image0, -1.0 );
    BOOST_CHECK( checkEqual( data0, 0 ) );

    BasicUtils::change_contrast( &image1, 1.0 );
    BOOST_CHECK( checkEqual( data1, 1 ) );
    BasicUtils::change_contrast( &image1, -1.0 );
    BasicUtils::change_contrast( &image1, -1.0 );
    BOOST_CHECK( checkEqual( data1, 1 ) );
}
BOOST_AUTO_TEST_CASE( contrast_2 )
{
    BasicUtils::change_contrast( &image0, 2.0 );
    byte aa[] { 21, 51, 95, 77 };
    BOOST_CHECK( checkEqual( aa, 0 ) );
    BasicUtils::change_contrast( &image0, 0.5 );
    BOOST_CHECK( checkEqual( data0, 0 ) );
}
BOOST_AUTO_TEST_CASE( contrast_3 )
{
    BasicUtils::change_contrast( &image0, -1.0 );
    byte aa[] { 181, 166, 144, 153 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    BasicUtils::change_contrast( &image1, -1.0 );
    byte bb[] { 255, 1, 0, 254 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
}

BOOST_AUTO_TEST_SUITE_END()




