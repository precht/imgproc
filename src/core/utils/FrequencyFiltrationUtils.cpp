#include "core/utils/FrequencyFiltrationUtils.hpp"

#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <functional>

using std::vector;
using std::complex;
using boost::numeric::ublas::matrix;
using std::unique_ptr;

namespace imgproc
{
namespace core
{
	matrix<complex<double>> FrequencyFiltrationUtils::imageTOcomplex( Image& input)
	{
		const int rows = input.rows();
		const int cols = input.columns();

		matrix<complex<double>> mat(rows, cols);

		for (int c = 0; c < input.channels(); c++)
		{
			// copy image to complex matrix
			for (int a = 0; a < rows; a++)
				for (int b = 0; b < cols; b++)
					mat(a, b) = input.at(a, b, c);
		}
		return mat;
	}
	unique_ptr<vector<matrix<complex<double>>>> FrequencyFiltrationUtils::LowPassFilter(vector<matrix<complex<double>>>& mats, int bandsize)
	{
		unique_ptr<vector<matrix<complex<double>>>> mats_ptr(new vector<matrix<complex<double>>>());
		
		auto& mat = mats[0];
		const int rows = mat.size1();
		const int cols = mat.size2();

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if ((sqrt((i - rows / 2)*(i - rows / 2) + (j - cols / 2)*(j - cols / 2))) < bandsize);
				else mat(i, j) = complex<double>(0, 0);
			}
		}
		mats_ptr->push_back(mat);
		return mats_ptr;
	}
	unique_ptr<vector<matrix<complex<double>>>> FrequencyFiltrationUtils::HighPassFilter(vector<matrix<complex<double>>>& mats, int bandsize)
	{
		unique_ptr<vector<matrix<complex<double>>>> mats_ptr(new vector<matrix<complex<double>>>());

		auto& mat = mats[0];
		const int rows = mat.size1();
		const int cols = mat.size2();

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if ((sqrt((i - rows / 2)*(i - rows / 2) + (j - cols / 2)*(j - cols / 2))) < bandsize)	mat(i, j) = complex<double>(0, 0);
			}
		}
		mats_ptr->push_back(mat);
		return mats_ptr;
	}
	unique_ptr<vector<matrix<complex<double>>>> FrequencyFiltrationUtils::BandCutFilter(vector<matrix<complex<double>>>& mats, int min, int max)
	{
		unique_ptr<vector<matrix<complex<double>>>> mats_ptr(new vector<matrix<complex<double>>>());

		auto& mat = mats[0];
		const int rows = mat.size1();
		const int cols = mat.size2();

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				double x = sqrt((i - rows / 2)*(i - rows / 2) + (j - cols / 2)*(j - cols / 2));
				if ((x <= max) && (x >= min))mat(i, j) = complex<double>(0, 0);
				
			}
		}
		mats_ptr->push_back(mat);
		return mats_ptr;
	}
}//core
}//imgproc