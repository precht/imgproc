
#include "img/ImageCV.hpp"
#include "img/utils.hpp"
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

BOOST_FIXTURE_TEST_SUITE(ImageUtilsTests, Image_F)

// Initial Fixture SetUp
BOOST_AUTO_TEST_CASE(ImageFixtureTest)
{
    BOOST_CHECK(!check_if_different(image1, data1, x1, y1, ch1, true));
//    cout << image1 << endl;
}

BOOST_AUTO_TEST_SUITE_END()




