#include "core/utils/FrequencyDomainUtils.hpp"
#include <iostream>
#include <stdexcept>

using std::complex;

namespace imgproc {
namespace core {

const double FrequencyDomainUtils::PI { std::acos(-1) };
const std::complex<double>  FrequencyDomainUtils::I { 0, 1 };

std::unique_ptr<boost::numeric::ublas::matrix<std::complex<double>>> FrequencyDomainUtils::fastFourierTransform(
        const Image& image)
{
    const int rows = image.rows();
    const int cols = image.columns();

    if (!isPowerOfTwo(rows) || !isPowerOfTwo(cols))
        throw std::invalid_argument("FFT failed, image size must be power of two.");

    std::unique_ptr<boost::numeric::ublas::matrix<std::complex<double>>> mat_ptr(
                new boost::numeric::ublas::matrix<std::complex<double>>(rows, cols));
    boost::numeric::ublas::matrix<std::complex<double>>& mat = *(mat_ptr.get());

    for (int a = 0; a < rows; a++)
        for (int b = 0; b < cols; b++)
            mat(a, b) = image.at(a, b, 0);

    for (int i = 0; i < rows; i++)
        FFT(mat, i, TT_ROW);

    for (int i = 0; i < cols; i++)
        FFT(mat, i, TT_COLUMN);

    return mat_ptr;
}

void FrequencyDomainUtils::inverseFastFourierTransform(Image& image,
        std::unique_ptr<boost::numeric::ublas::matrix<std::complex<double>>> matrix_ptr)
{
    boost::numeric::ublas::matrix<std::complex<double>>& mat = *(matrix_ptr.get());
    const int rows = mat.size1();
    const int cols = mat.size2();

    if (!isPowerOfTwo(rows) || !isPowerOfTwo(cols))
        throw std::invalid_argument("IFFT failed, image size must be power of two.");

    for (int i = 0; i < cols; i++)
        IFFT(mat, i, TT_COLUMN);

    for (int i = 0; i < rows; i++)
        IFFT(mat, i, TT_ROW);

    for (int a = 0; a < rows; a++)
        for (int b = 0; b < cols; b++)
            image(a, b, 0) = mat(a, b).real();
}

void FrequencyDomainUtils::FFT(boost::numeric::ublas::matrix<std::complex<double>>& mat,
                               int position, TransformType type)
{
    bitReverse(mat, position, type);

    const int size = (type == TT_ROW ? mat.size2() : mat.size1());
    const int lsize = std::log2(size);
    for(int s = 1; s <= lsize; s++)
    {
        const int m = 2 << (s - 1);
        complex<double> wm = std::exp(2 * PI / m * I);
        for(int k = 0; k < size; k += m)
        {
            complex<double> w{1, 0};
            const int mh = m >> 1;
            for(int j = 0; j < mh; ++j)
            {
                const int fst = k + j;
                const int snd = fst + mh;
                if(type == TT_ROW)
                {
                    complex<double> t = mat(position, fst);
                    complex<double> u = w * mat(position, snd);
                    mat(position, fst) = t + u;
                    mat(position, snd) = t - u;
                }
                else
                {
                    complex<double> t = mat(fst, position);
                    complex<double> u = w * mat(snd, position);
                    mat(fst, position) = t + u;
                    mat(snd, position) = t - u;
                }
                w *= wm;
            }
        }
    }
}

void FrequencyDomainUtils::IFFT(boost::numeric::ublas::matrix<std::complex<double>>& mat,
                                int position, TransformType type)
{
    bitReverse(mat, position, type);

    const int size = (type == TT_ROW ? mat.size2() : mat.size1());
    const int lsize = std::log2(size);
    for(int s = 1; s <= lsize; s++)
    {
        const int m = 2 << (s - 1);
        complex<double> wm = std::exp(-2 * PI / m * I);
        for(int k = 0; k < size; k += m)
        {
            complex<double> w{1, 0};
            const int mh = m >> 1;
            for(int j = 0; j < mh; ++j)
            {
                const int fst = k + j;
                const int snd = fst + mh;
                if(type == TT_ROW)
                {
                    complex<double> t = mat(position, fst);
                    complex<double> u = w * mat(position, snd);
                    mat(position, fst) = t + u;
                    mat(position, snd) = t - u;
                }
                else
                {
                    complex<double> t = mat(fst, position);
                    complex<double> u = w * mat(snd, position);
                    mat(fst, position) = t + u;
                    mat(snd, position) = t - u;
                }
                w *= wm;
            }
        }
    }
    for(int i = 0; i < size; i++)
    {
        if(type == TT_ROW) mat(position, i) /= size;
        else mat(i, position) /= size;
    }
}

bool FrequencyDomainUtils::isPowerOfTwo(int number)
{
    int count;
    for (count = 0; number; count++)
    {
      number &= number - 1;
    }
    return (count == 1);
}

void FrequencyDomainUtils::bitReverse(boost::numeric::ublas::matrix<std::complex<double>>& mat,
                                      int position, TransformType type)
{
    const int size = (type == TT_ROW ? mat.size2() : mat.size1());
    const int lsize = std::log2(size);
    for (int i = 0; i < (size >> 1) ; i++)
    {
        int v = i;
        int r = 0;
        for (int s = lsize - 1; s; v >>= 1, r <<= 1, s--) r |= v & 1;
        r |= v & 1;
        if (type == TT_ROW) swap(mat(position, i), mat(position, r));
        else swap(mat(i, position), mat(r, position));
    }
}

} // !core
} // !imgproc
