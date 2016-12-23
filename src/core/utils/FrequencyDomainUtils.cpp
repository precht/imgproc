#include "core/utils/FrequencyDomainUtils.hpp"

#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <stdexcept>
#include <limits>

using std::complex;

namespace imgproc {
namespace core {

const double FrequencyDomainUtils::PI { std::acos(-1) };
const std::complex<double>  FrequencyDomainUtils::I { 0, 1 };

std::unique_ptr<std::vector<boost::numeric::ublas::matrix<std::complex<double>>>>
        FrequencyDomainUtils::fastFourierTransform(const Image& input)
{
    std::unique_ptr<std::vector<boost::numeric::ublas::matrix<std::complex<double>>>> mats_ptr(
                new std::vector<boost::numeric::ublas::matrix<std::complex<double>>>());

    for (int c = 0; c < input.channels(); c++)
    {
        const int rows = input.rows();
        const int cols = input.columns();

        if (!isPowerOfTwo(rows) || !isPowerOfTwo(cols))
            throw std::invalid_argument("FFT failed, image size must be power of two.");

        boost::numeric::ublas::matrix<std::complex<double>> mat(rows, cols);

        for (int a = 0; a < rows; a++)
            for (int b = 0; b < cols; b++)
                mat(a, b) = input.at(a, b, c);

        for (int i = 0; i < rows; i++)
            FFT(mat, i, TT_ROW);

        for (int i = 0; i < cols; i++)
            FFT(mat, i, TT_COLUMN);

        for (int a = 0; a < (rows >> 1); a++)
            for (int b = 0; b < cols; b++)
                swap(mat(a, b), mat((a + (rows >> 1)) % rows, (b + (cols >> 1)) % cols));

        // TODO: boost matrix does not have move constructor
        mats_ptr->push_back(mat);
    }
    return mats_ptr;
}

void FrequencyDomainUtils::inverseFastFourierTransform(Image& output,
        std::vector<boost::numeric::ublas::matrix<std::complex<double>>>& mats)
{
    if (output.channels() != (int)mats.size())
        throw std::invalid_argument("IFFT failed, output image and input matrix must have same number of channels.");

    for (int c = 0; c < output.channels(); c++)
    {
        auto& mat = mats[c];
        const int rows = mat.size1();
        const int cols = mat.size2();

        if (!isPowerOfTwo(rows) || !isPowerOfTwo(cols))
            throw std::invalid_argument("IFFT failed, image size must be power of two.");

        for (int a = 0; a < (rows >> 1); a++)
            for (int b = 0; b < cols; b++)
                swap(mat(a, b), mat((a + (rows >> 1)) % rows, (b + (cols >> 1)) % cols));

        for (int i = 0; i < cols; i++)
            IFFT(mat, i, TT_COLUMN);

        for (int i = 0; i < rows; i++)
            IFFT(mat, i, TT_ROW);

        for (int a = 0; a < rows; a++)
            for (int b = 0; b < cols; b++)
                output(a, b, c) = round(mat(a, b).real());
    }
}

void FrequencyDomainUtils::complexMatrixToImages(
        const std::vector<boost::numeric::ublas::matrix<std::complex<double>>>& mats,
        Image& output1, Image& output2, ConvertType type)
{
    if (output1.channels() != (int)mats.size() || output2.channels() != (int)mats.size())
        throw std::invalid_argument("matrix to images convert failed, output images and input matrix"
                                    "must have same number of channels.");

    for (int c = 0; c < output1.channels(); c++)
    {
        auto& mat = mats[c];
        const int rows = mat.size1();
        const int cols = mat.size2();

        if (output1.rows() != rows || output2.rows() != rows || output1.columns() != cols || output2.columns() != cols)
            throw std::invalid_argument("matrix to images convert failed, images and matrix must have the same size.");

        if (type == CT_PHASE_MAGNITUDE) // magnitude has logarithmic scale and phase has normal
        {
            boost::numeric::ublas::matrix<double> tab1(rows, cols);
            boost::numeric::ublas::matrix<double> tab2(rows, cols);
            double min1 = std::numeric_limits<double>::max();
            double min2 = std::numeric_limits<double>::max();
            double max1 = std::numeric_limits<double>::lowest();
            double max2 = std::numeric_limits<double>::lowest();

            for (int a = 0; a < rows; a++)
            {
                for (int b = 0; b < cols; b++)
                {
                    tab1(a, b) = std::log(std::sqrt(std::pow(mat(a, b).real(), 2) + std::pow(mat(a, b).imag(), 2)));
                    tab2(a, b) = std::atan(mat(a, b).imag() / mat(a, b).real());
                    if(min1 > tab1(a, b)) min1 = tab1(a, b);
                    if(max1 < tab1(a, b)) max1 = tab1(a, b);
                    if(min2 > tab2(a, b)) min2 = tab2(a, b);
                    if(max2 < tab2(a, b)) max2 = tab2(a, b);
                }
            }

            double scale1 = 255.0 / (max1 - min1);
            double shift1 = -min1;
            double scale2 = 255.0 / (max2 - min2);
            double shift2 = -min2;
            for (int a = 0; a < rows; a++)
            {
                for (int b = 0; b < cols; b++)
                {
                    output1(a, b, c) = scale1 * (tab1(a, b) + shift1);
                    output2(a, b, c) = scale2 * (tab2(a, b) + shift2);
                }
            }
        }
        else // real and imaginary parts have noraml scale
        {
            double min1 = mat(0, 0).real();
            double min2 = mat(0, 0).imag();
            double max1 = mat(0, 0).real();
            double max2 = mat(0, 0).imag();
            for (int a = 0; a < rows; a++)
            {
                for (int b = 0; b < cols; b++)
                {
                    if (max1 < mat(a, b).real()) max1 = mat(a, b).real();
                    if (min1 > mat(a, b).real()) min1 = mat(a, b).real();
                    if (max2 < mat(a, b).imag()) max2 = mat(a, b).imag();
                    if (min2 > mat(a, b).imag()) min2 = mat(a, b).imag();
                }
            }

            double scale1 = 255.0 / (max1 - min1);
            double shift1 = -min1;
            double scale2 = 255.0 / (max2 - min2);
            double shift2 = -min2;
            for (int a = 0; a < rows; a++)
            {
                for (int b = 0; b < cols; b++)
                {
                    output1(a, b, c) = scale1 * (mat(a, b).real() + shift1);
                    output2(a, b, c) = scale2 * (mat(a, b).imag() + shift2);
                }
            }
        }
    }
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
    if (size < 2) return; // nothing to do. also log2(1) is 0 and it breaks this algorithm
    const int lsize = std::log2(size);
    for (int i = 0; i < size ; i++)
    {
        int v = i;
        int r = 0;
        for (int s = lsize - 1; s; v >>= 1, r <<= 1, s--) r |= v & 1;
        r |= v & 1;
        if(i < r)
        {
            if (type == TT_ROW) swap(mat(position, i), mat(position, r));
            else swap(mat(i, position), mat(r, position));
        }
    }
}

} // !core
} // !imgproc
