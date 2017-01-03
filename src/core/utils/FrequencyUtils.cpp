#include "core/utils/FrequencyUtils.hpp"

#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <thread>
#include <functional>

using std::thread;
using std::vector;
using std::complex;
using std::unique_ptr;
using boost::numeric::ublas::matrix;

namespace imgproc {
namespace core {

const double FrequencyUtils::PI { std::acos(-1) };
const complex<double>  FrequencyUtils::I { 0, 1 };

unique_ptr<vector<matrix<complex<double>>>> FrequencyUtils::fastFourierTransform(const Image& input)
{
    unique_ptr<vector<matrix<complex<double>>>> mats_ptr(new vector<matrix<complex<double>>>());

    for (int c = 0; c < input.channels(); c++)
    {
        const int rows = input.rows();
        const int cols = input.columns();

        if (!isPowerOfTwo(rows) || !isPowerOfTwo(cols))
            throw std::invalid_argument("FFT failed, image size must be power of two.");

        matrix<complex<double>> mat(rows, cols);

        // copy image to complex matrix
        for (int a = 0; a < rows; a++)
            for (int b = 0; b < cols; b++)
                mat(a, b) = input.at(a, b, c);

        // get threads number
        int thr_num = thread::hardware_concurrency();
        if (thr_num <= 0) thr_num = 1;
        vector<thread> thrs;

        // transform rows
        for (int i = 1; i < thr_num; i++)
            thrs.push_back(std::move(thread(threadFftLoop, i, thr_num, rows, std::ref(mat), TT_ROW)));
        threadFftLoop(0, thr_num, rows, std::ref(mat), TT_ROW);

        for (auto it = thrs.begin(); it != thrs.end(); ++it) it->join();
        thrs.clear();

        // transform columns
        for (int i = 1; i < thr_num; i++)
            thrs.push_back(std::move(thread(threadFftLoop, i, thr_num, cols, std::ref(mat), TT_COLUMN)));
        threadFftLoop(0, thr_num, cols, std::ref(mat), TT_COLUMN);

        for (auto it = thrs.begin(); it != thrs.end(); ++it) it->join();
        thrs.clear();

        // swap image squares (4 squares, swapping diagonally)
        for (int a = 0; a < (rows >> 1); a++)
            for (int b = 0; b < cols; b++)
                swap(mat(a, b), mat((a + (rows >> 1)) % rows, (b + (cols >> 1)) % cols));

        // TODO: boost matrix does not have move constructor
        mats_ptr->push_back(mat);
    }
    return mats_ptr;
}

void FrequencyUtils::threadFftLoop(int thr_id, int thr_num, int range, matrix<complex<double>>& mat, TransformType type)
{
    for (; thr_id < range; thr_id += thr_num)
        fftDit(mat, thr_id, type);
}

void FrequencyUtils::inverseFastFourierTransform(Image& output, vector<matrix<complex<double>>>& mats)
{
	if (output.channels() != (int)mats.size())
		output.resize(mats[0].size1(), mats[0].size2(), mats.size());
       // throw std::invalid_argument("IFFT failed, output image and input matrix must have same number of channels.");

    for (int c = 0; c < output.channels(); c++)
    {
        auto& mat = mats[c];
        const int rows = mat.size1();
        const int cols = mat.size2();

        if (!isPowerOfTwo(rows) || !isPowerOfTwo(cols))
            throw std::invalid_argument("IFFT failed, image size must be power of two.");

        // swap image squares (4 squares, swapping diagonally)
        for (int a = 0; a < (rows >> 1); a++)
            for (int b = 0; b < cols; b++)
                swap(mat(a, b), mat((a + (rows >> 1)) % rows, (b + (cols >> 1)) % cols));

        // get threads number
        int thr_num = thread::hardware_concurrency();
        if (thr_num <= 0) thr_num = 1;
        vector<thread> thrs;

        // transform columns
        for (int i = 1; i < thr_num; i++)
            thrs.push_back(std::move(thread(threadIfftLoop, i, thr_num, cols, std::ref(mat), TT_COLUMN)));
        threadIfftLoop(0, thr_num, cols, std::ref(mat), TT_COLUMN);

        for (auto it = thrs.begin(); it != thrs.end(); ++it) it->join();
        thrs.clear();

        // transform rows
        for (int i = 1; i < thr_num; i++)
            thrs.push_back(std::move(thread(threadIfftLoop, i, thr_num, rows, std::ref(mat), TT_ROW)));
        threadIfftLoop(0, thr_num, rows, std::ref(mat), TT_ROW);

        for (auto it = thrs.begin(); it != thrs.end(); ++it) it->join();
        thrs.clear();

        // write result
        for (int a = 0; a < rows; a++)
            for (int b = 0; b < cols; b++)
                output(a, b, c) = round(mat(a, b).real());
    }
}

void FrequencyUtils::threadIfftLoop(int thr_id, int thr_num, int range, matrix<complex<double>>& mat, TransformType type)
{
    for (; thr_id < range; thr_id += thr_num)
        ifftDit(mat, thr_id, type);
}

void FrequencyUtils::fftDit(matrix<complex<double>>& mat, int position, TransformType type)
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

void FrequencyUtils::ifftDit(matrix<complex<double>>& mat, int position, TransformType type)
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

bool FrequencyUtils::isPowerOfTwo(int number)
{
    int count;
    for (count = 0; number; count++)
    {
        number &= number - 1;
    }
    return (count == 1);
}

void FrequencyUtils::bitReverse(matrix<complex<double>>& mat, int position, TransformType type)
{
    const int size = (type == TT_ROW ? mat.size2() : mat.size1());
    if (size < 2) return; // nothing to do. also log2(1) is 0 and it breaks second loop
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

void FrequencyUtils::complexMatrixToImages(const vector<matrix<complex<double>>>& mats,
                                           Image& output1, Image& output2, ConvertType type)
{
   /* if (output1.channels() != (int)mats.size() || output2.channels() != (int)mats.size())
        throw std::invalid_argument("matrix to images convert failed, output images and input matrix"
                                    "must have same number of channels.");
									*/
	if (output1.channels() != (int)mats.size() || output2.channels() != (int)mats.size())
	{
		output1.resize(mats[0].size1(), mats[0].size2(), mats.size());
		output2.resize(mats[0].size1(), mats[0].size2(), mats.size());
	}
    for (int c = 0; c < output1.channels(); c++)
    {
        auto& mat = mats[c];
        const int rows = mat.size1();
        const int cols = mat.size2();

		if (output1.rows() != rows || output2.rows() != rows || output1.columns() != cols || output2.columns() != cols)
			throw std::invalid_argument("matrix to images convert failed, images and matrix must have the same size");
        if (type == CT_PHASE_MAGNITUDE) // magnitude has logarithmic scale and phase has normal
        {
            matrix<double> tab1(rows, cols);
            matrix<double> tab2(rows, cols);
            double min1 = std::numeric_limits<double>::max();
            double min2 = std::numeric_limits<double>::max();
            double max1 = std::numeric_limits<double>::lowest();
            double max2 = std::numeric_limits<double>::lowest();

            for (int a = 0; a < rows; a++)
            {
                for (int b = 0; b < cols; b++)
                {
                    // add 1 to avoid log(0)
                    tab1(a, b) = std::log(std::sqrt(std::pow(mat(a, b).real(), 2) + std::pow(mat(a, b).imag(), 2)) + 1);
                    tab2(a, b) = std::atan(mat(a, b).imag() / mat(a, b).real());
                    if(min1 > tab1(a, b)) min1 = tab1(a, b);
                    if(max1 < tab1(a, b)) max1 = tab1(a, b);
                    if(min2 > tab2(a, b)) min2 = tab2(a, b);
                    if(max2 < tab2(a, b)) max2 = tab2(a, b);
                }
            }

            // NOTE: min1 = 0 to prevent image after filtration from being brighter
            min1 = 0;

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

} // !core
} // !imgproc
