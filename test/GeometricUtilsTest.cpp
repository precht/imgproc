/**
 *      Purpose:    Tests for Geometric Utils ( horizontal, vertical, diagonal filps and scaling )
 *      Created:    16th Nov 2016
 *      Author:     Jakub Precht
 */

#include "img/ImageCV.hpp"
#include "img/utils/GeometricUtils.hpp"
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

BOOST_FIXTURE_TEST_SUITE( GeometricUtilsTests, ImageFixture )

//    data0[] { 74, 89, 111, 102 };
//    data1[] { 0, 254, 255, 1 };

BOOST_AUTO_TEST_CASE( horizontalFlip )
{
    GeometricUtils::flip_horizontally( &image0 );
    byte aa[] { 89, 74, 102, 111 };
    BOOST_CHECK( checkEqual( aa, 0 ) );
}

BOOST_AUTO_TEST_CASE( verticalFlip )
{
    GeometricUtils::flip_vertically( &image0 );
    byte aa[] { 111, 102, 74, 89 };
    BOOST_CHECK( checkEqual( aa, 0 ) );
}

BOOST_AUTO_TEST_CASE( diagonalFlip )
{
    GeometricUtils::flip_diagonally( &image0 );
    byte aa[] { 102, 111, 89, 74 };
    BOOST_CHECK( checkEqual( aa, 0 ) );
}

BOOST_AUTO_TEST_CASE( scale_1 )
{
    GeometricUtils::scale( &image0, 2.0 );
    byte aa[] {
        74,     74,     89,     89,
        74,     74,     89,     89,
       111,    111,    102,    102,
       111,    111,    102,    102
    };
    BOOST_CHECK( checkEqual( aa, image0, 4, 4, 1 ) );
}
BOOST_AUTO_TEST_CASE( scale_2 )
{
    GeometricUtils::scale( &image0, 0.5 );
    byte aa[] { 74 };
    BOOST_CHECK( checkEqual( aa, image0, 1, 1, 1 ) );
}
BOOST_AUTO_TEST_CASE( scale_3 )
{
    GeometricUtils::scale( &image0, 1.1 );
    BOOST_CHECK( checkEqual( data0, 0 ) );
}
BOOST_AUTO_TEST_CASE( scale_4 )
{
    GeometricUtils::scale( &image0, 1.5 );
    byte aa[] {
        74,     74,     89,
        74,     74,     89,
       111,    111,    102
    };
    BOOST_CHECK( checkEqual( aa, image0, 3, 3, 1 ) );
}

BOOST_AUTO_TEST_SUITE_END()



