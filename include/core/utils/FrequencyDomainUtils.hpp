#ifndef FREQUENCY_DOMAIN_UTILS_HPP_
#define FREQUENCY_DOMAIN_UTILS_HPP_

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"

#include <boost/numeric/ublas/matrix.hpp>
#include <complex>
#include <memory>
#include <cmath>

namespace imgproc
{
namespace core
{

enum TransformType { TT_ROW, TT_COLUMN };

// TODO fft for color images

class FrequencyDomainUtils
{
public:

    static std::unique_ptr<boost::numeric::ublas::matrix<std::complex<double>>> fastFourierTransform(
            const Image& input);

    static void inverseFastFourierTransform(Image& output,
            std::unique_ptr<boost::numeric::ublas::matrix<std::complex<double>>> input_matrix_ptr);

private:
    const static double PI;
    const static std::complex<double> I;

    static void FFT(boost::numeric::ublas::matrix<std::complex<double>>& mat, int position, TransformType type);
    static void IFFT(boost::numeric::ublas::matrix<std::complex<double>>& mat, int position, TransformType type);

    static bool isPowerOfTwo(int number);
    static void bitReverse(boost::numeric::ublas::matrix<std::complex<double>>& mat,
                                int position, TransformType type);
};

} // core
} // imgproc

#endif // FREQUENCY_DOMAIN_UTILS_HPP_
