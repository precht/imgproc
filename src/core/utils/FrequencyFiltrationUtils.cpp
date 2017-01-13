#include "core/utils/FrequencyFiltrationUtils.hpp"

#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <functional>
#include <cmath>

using boost::numeric::ublas::matrix;
using std::unique_ptr;
using std::complex;
using std::vector;
using std::pow;
using std::sqrt;

namespace imgproc
{
namespace core
{

const double FrequencyFiltrationUtils::PI{ std::acos(-1) };

//matrix<complex<double>> FrequencyFiltrationUtils::imageTOcomplex( Image& input)
//{
//    const int rows = input.rows();
//    const int cols = input.columns();

//    matrix<complex<double>> mat(rows, cols);

//    for (int c = 0; c < input.channels(); c++)
//    {
//        // copy image to complex matrix
//        for (int a = 0; a < rows; a++)
//            for (int b = 0; b < cols; b++)
//                mat(a, b) = input.at(a, b, c);
//    }
//    return mat;
//}

void FrequencyFiltrationUtils::lowPassFilter(vector<matrix<complex<double>>>& mats, int bandsize)
{
    const int chns = mats.size();
    for (int c = 0; c < chns; c++)
    {
        const int rows = mats[c].size1();
        const int cols = mats[c].size2();
        for (int x = 0; x < rows; ++x)
        {
            const auto x_distance = pow(x - (rows >> 1), 2);
            for (int y = 0; y < cols; ++y)
                if (sqrt(x_distance + pow(y - (cols >> 1), 2)) > bandsize)
                    mats[c](x, y) = complex<double>(0, 0);
        }
    }
}

void FrequencyFiltrationUtils::highPassFilter(vector<matrix<complex<double>>>& mats, int bandsize)
{
    const int chns = mats.size();
    for (int c = 0; c < chns; c++)
    {
        const int rows = mats[c].size1();
        const int cols = mats[c].size2();
        auto spectral_val = mats[c](rows >> 1, cols >> 1); // should remain unchanged
        for (int x = 0; x < rows; ++x)
        {
            const auto x_distance = pow(x - (rows >> 1), 2);
            for (int y = 0; y < cols; ++y)
                if (sqrt(x_distance + pow(y - (cols >> 1), 2)) <= bandsize)
                    mats[c](x, y) = complex<double>(0, 0);
        }
        mats[c](rows >> 1, cols >> 1) = spectral_val;
    }
}

void FrequencyFiltrationUtils::bandCutFilter(vector<matrix<complex<double>>>& mats, int min, int max)
{
    const int chns = mats.size();
    for (int c = 0; c < chns; c++)
    {
        const int rows = mats[c].size1();
        const int cols = mats[c].size2();
        for (int x = 0; x < rows; ++x)
        {
            const auto x_distance = pow(x - (rows >> 1), 2);
            for (int y = 0; y < cols; ++y)
            {
                const auto t = sqrt(x_distance +  pow(y - (cols >> 1), 2));
                if (t <= max && t >= min)
                    mats[c](x, y) = complex<double>(0, 0);
            }
        }
    }
}

void FrequencyFiltrationUtils::highPassWithEdgeDetFilter(vector<matrix<complex<double>>>& mats, int variant, int bandsize)
{
    Image mask(std::make_shared<opencv::OpenCVImageHelper>());
    switch (variant)
    {
    case 1: mask.load("F5mask1.bmp"); break;
    case 2: mask.load("F5mask2.bmp"); break;
    default: mask.load("F5mask1.bmp"); break;
    }

    const double inv_max_color = 1.0 / 255.0;

    const int chns = mats.size();

    for (int c = 0; c < chns; c++)
    {
        const int rows = mats[c].size1();
        const int cols = mats[c].size2();

        if (mask.rows() != rows || mask.columns() != cols)
            throw "HPWED: Wrong mask size!";

        auto spectral_val = mats[c](rows >> 1, cols >> 1);

        for (int x = 0; x < rows; ++x)
        {
            const auto x_distance = pow(x - (rows >> 1), 2);
            for (int y = 0; y < cols; ++y)
                if (sqrt(x_distance + pow(y - (cols >> 1), 2)) <= bandsize) mats[c](x, y) = complex<double>{0,0};
                else mats[c](x, y) *= mask(x, y, c) * inv_max_color;
        }
        mats[c](rows >> 1, cols >> 1) = spectral_val;
    }
}

void FrequencyFiltrationUtils::phaseModFilter(vector<matrix<complex<double>>>& mats, int k, int l)
{
    const int chns = mats.size();
    const auto z_comp = (k + l) * PI;
    for (int c = 0; c < chns; c++)
    {
        const int rows = mats[c].size1();
        const int cols = mats[c].size2();
        const double inv_rows = 1.0 / rows;
        const double inv_cols = 1.0 / cols;
        for (int x = 0; x < rows; ++x)
        {
            const auto x_comp = -x * k * 2 * inv_rows * PI;
            for (int y = 0; y < cols; ++y)
            {
                const auto t = (x_comp + (-y * l * 2 * inv_cols * PI) + z_comp);
                mats[c](x, y) *= complex<double>(cos(t), sin(t));
            }
        }
    }
}

}//core
}//imgproc
