/**
 *      Purpose:    Tests for NoiseRemovalUtils ( geometric mean filter and alpha trimmed mean filter)
 *      Created:    16th Nov 2016
 *      Author:     Jakub Precht
 */

#include "img/ImageCV.hpp"
#include "img/utils/NoiseRemovalUtils.hpp"
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

BOOST_FIXTURE_TEST_SUITE( NoiseRemovalUtilsTests, ImageFixture )

//    data0[] { 74, 89, 111, 102 };
//    data1[] { 0, 254, 255, 1 };

BOOST_AUTO_TEST_CASE( geometricMeanFilter )
{
    NoiseRemovalUtils::geometric_mean_filter( &image0 );
    byte aa[] { 87, 90, 97, 97 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    NoiseRemovalUtils::geometric_mean_filter( &image1 );
    byte bb[] { 0, 0, 0, 0 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
}

BOOST_AUTO_TEST_CASE( alphaTrimmedMeanFilter_1 )
{
    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image0, 0 );
    byte aa[] { 88, 91, 98, 98 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image1, 0 );
    byte bb[] { 113, 141, 141, 113 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
}
BOOST_AUTO_TEST_CASE( alphaTrimmedMeanFilter_2 )
{
    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image0, 1 );
    byte aa[] { 87, 90, 100, 99 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image1, 1 );
    byte bb[] { 109, 145, 145, 109 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
}
BOOST_AUTO_TEST_CASE( alphaTrimmedMeanFilter_3 )
{
    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image0, 2 );
    byte aa[] { 85, 91, 103, 99 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image1, 2 );
    byte bb[] { 101, 152, 153, 102 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
}
BOOST_AUTO_TEST_CASE( alphaTrimmedMeanFilter_4 )
{
    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image0, 3 );
    byte aa[] { 84, 89, 105, 102 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image1, 3 );
    byte bb[] { 85, 169, 170, 85 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
}
BOOST_AUTO_TEST_CASE( alphaTrimmedMeanFilter_5 )
{
    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image0, 4 );
    byte aa[] { 89, 89, 102, 102 };
    BOOST_CHECK( checkEqual( aa, 0 ) );

    NoiseRemovalUtils::alpha_trimmed_mean_filter( &image1, 4 );
    byte bb[] { 1, 254, 254, 1 };
    BOOST_CHECK( checkEqual( bb, 1 ) );
}

BOOST_AUTO_TEST_SUITE_END()



