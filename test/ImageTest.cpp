
#include "img/Image.hpp"
#include "img/ImageCV.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>

using namespace imgprocapp::img;

BOOST_AUTO_TEST_SUITE( ImageTests )

BOOST_AUTO_TEST_CASE( empty )
{
    Image &img = *new ImageCV();
    delete &img;
}
BOOST_AUTO_TEST_CASE( set_size )
{
    Image &img = *new ImageCV( 11, 22, 3 );
    BOOST_CHECK_EQUAL( img.rows(), 11 );
    BOOST_CHECK_EQUAL( img.columns(), 22 );
    BOOST_CHECK_EQUAL( img.channels(), 3 );
    delete &img;
}
BOOST_AUTO_TEST_CASE( get_set_values )
{
    Image &img = *new ImageCV( 2, 3, 3 );
    for ( unsigned char i = 0; i < 18; i++ ) img( i ) = i;
    for ( unsigned char i = 0; i < 18; i++ ) BOOST_CHECK_EQUAL( img( i ), i );
    for ( int x = 0; x < 2; x++)
        for ( int y = 0; y < 3; y++)
            for ( int c = 0; c < 3; c++)
            {
                BOOST_CHECK_EQUAL( img( x, y, c ), ( x * 9 ) + ( y * 3 ) + c );
                img( x, y, c ) = 17 - ( x * 9 ) - ( y * 3 ) - c;
            }
    for ( unsigned char i = 0; i < 18; i++ ) BOOST_CHECK_EQUAL( img( i ), 17 - i );
    delete &img;
}

BOOST_AUTO_TEST_CASE( set_data )
{
    unsigned char data[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    Image &img = *new ImageCV( 2, 2, 3, data );
    BOOST_CHECK_EQUAL( img.rows(), 2 );
    BOOST_CHECK_EQUAL( img.columns(), 2 );
    BOOST_CHECK_EQUAL( img.channels(), 3 );
    for ( int i = 0; i < 12; i++ ) BOOST_CHECK_EQUAL( img( i ), i );
    for ( int x = 0; x < 2; x++)
        for ( int y = 0; y < 2; y++)
            for ( int c = 0; c < 3; c++)
                BOOST_CHECK_EQUAL( img( x, y, c ), ( x * 6 ) + ( y * 3 ) + c );
    delete &img;
}
BOOST_AUTO_TEST_CASE( set_names )
{
    unsigned char data[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    Image &img = *new ImageCV( 2, 2, 3, data );;
    for ( int i = 0; i < 12; i++ ) BOOST_REQUIRE_EQUAL( img( i ), i );

    std::string name{ "a_test.bmp" };
    img.set_output_name( name );
    img.save_image();
    delete &img;

//    img = *new ImageCV( name, "" );
//    for ( int i = 0; i < 12; i++ ) BOOST_CHECK_EQUAL( img( i ), i );
//    delete &img;

    boost::filesystem::remove( name );
}


BOOST_AUTO_TEST_SUITE_END()
