#include "core/Image.hpp"
#include "core/utils/FrequencyUtils.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <complex>
#include <iostream>
#include <iomanip>
#include <cmath>

using fu = imgproc::core::FrequencyUtils;

using std::complex;
using std::cout;
using std::endl;

BOOST_AUTO_TEST_SUITE(FrequencyDomainTests)


BOOST_AUTO_TEST_CASE(fft_ifft)
{
    imgproc::core::Image img1(512, 1024, 3);
    for(int i = 0; i <  512 * 1024 * 3; i++) img1(i) = i;
    imgproc::core::Image img2(img1);
    fu::inverseFastFourierTransform(img1, *fu::fastFourierTransform(img1).get());
    BOOST_CHECK_EQUAL(img1, img2);
}

BOOST_AUTO_TEST_SUITE_END()
