#include "core/Image.hpp"
#include "core/utils/FrequencyDomainUtils.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <complex>
#include <iostream>
#include <iomanip>
#include <cmath>

using fdu = imgproc::core::FrequencyDomainUtils;

using std::complex;
using std::cout;
using std::endl;

BOOST_AUTO_TEST_SUITE(FrequencyDomainTests)

BOOST_AUTO_TEST_CASE(xxx)
{
    imgproc::core::Image img1(4, 8, 1);
    for(int i = 0; i < img1.size(); i++) img1(i) = i;
    imgproc::core::Image img2(img1);
    fdu::inverseFastFourierTransform(img1, fdu::fastFourierTransform(img1));
    BOOST_CHECK_EQUAL(img1, img2);
}

BOOST_AUTO_TEST_SUITE_END()
