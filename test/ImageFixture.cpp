/**
 *      Purpose:    Fixture class for utils tests
 *      Created:    13th Nov 2016
 *      Author:     Jakub Precht
 */

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

DataSet::DataSet( imgprocapp::img::ImageCV &aImage, int aX, int aY, int aCh )
    : image( aImage )
    , x( aX )
    , y( aY )
    , ch( aCh )
{ }

ImageFixture::ImageFixture()
    : image0( x0, y0, ch0, data0_copy )
    , image1( x1, y1, ch1, data1_copy )
    , image2( x2, y2, ch2, data2_copy )
{
    data_sets_.push_back( DataSet( image0, x0, y0, ch0 ) );
    data_sets_.push_back( DataSet( image1, x1, y1, ch1 ) );
    data_sets_.push_back( DataSet( image2, x2, y2, ch2 ) );

    std::copy( data0, data0 + size0, data0_copy );
    std::copy( data1, data1 + size1, data1_copy );
    std::copy( data2, data2 + size2, data2_copy );
}

bool ImageFixture::checkEqual( const byte *data, int index, bool use_test_check )
{
    return checkEqual( data, data_sets_[index].image, data_sets_[index].x, data_sets_[index].y,
                       data_sets_[index].ch, use_test_check );
}

bool ImageFixture::checkEqual( const byte *data, ImageCV &A, int x, int y, int ch, bool use_test_check )
{
    bool is_correct = true;
    for ( int i = 0; i < x; ++i )
        for ( int j = 0; j < y; ++j )
            for ( int k = 0; k < ch; ++k )
            {
                is_correct &= data[ ( i * y * ch ) + ( j * ch ) + k ] == *A.ptr( i, j, k );
                if ( use_test_check ) BOOST_CHECK_EQUAL( data[ ( i * y * ch ) + ( j * ch ) + k ], *A.ptr( i, j, k ) );
            }

    return is_correct;
}

const byte ImageFixture::data0[] = {
    74,    89,
   111,   102
};

const byte ImageFixture::data1[] = {
     0,   254,
   255,     1
};

const byte ImageFixture::data2[] {
    20,  38,  15,    204, 181,  74,     93, 241,  63,
    89,  58, 172,    138,  58, 235,    195,   0,  51,
   179, 255, 157,     45, 103, 231,     18,  16,   0,
   138,  48,  61,    246,   1,  73,    158,  92, 173
};
