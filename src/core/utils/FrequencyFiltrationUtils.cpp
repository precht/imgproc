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
	const double FrequencyFiltrationUtils::PI{ std::acos(-1) };

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
		
		auto spectral_component = mat(rows / 2, cols / 2);

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if ((sqrt((i - rows / 2)*(i - rows / 2) + (j - cols / 2)*(j - cols / 2))) < bandsize)	mat(i, j) *= complex<double>(0, 0);				
			}
		}
		mat(rows / 2, cols / 2) = spectral_component;
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

	unique_ptr<vector<matrix<complex<double>>>> FrequencyFiltrationUtils::HighPassWithEdgeDetFilter(vector<matrix<complex<double>>>& mats, int variant , int bandsize)
	{
		unique_ptr<vector<matrix<complex<double>>>> mats_ptr(new vector<matrix<complex<double>>>());

		auto& mat1 = mats[0];
		auto& mat2 = mats[1];
		auto& mat3 = mats[2];
		const int rows = mat1.size1();
		const int cols = mat1.size2();
		Image input(std::make_shared<opencv::OpenCVImageHelper>());
		switch (variant)
		{
		case 1: input.load("horizontal.bmp"); break;
		case 2: input.load("horizontalanddiagonal.bmp"); break;
		default: input.load("horizontal.bmp"); break;
		}
		const int mask_rows = input.rows();
		const int mask_cols = input.columns();

		auto spectral_component1 = mat1(rows / 2, cols / 2);
		auto spectral_component2 = mat2(rows / 2, cols / 2);
		auto spectral_component3 = mat3(rows / 2, cols / 2);

		matrix<complex<double>> mask(mask_rows, mask_cols);
		for (int x = 0; x < mask_rows; ++x) 
		{
			for (int y = 0; y < mask_cols; ++y)
			{
				for (int c = 0; c < input.channels(); ++c)
				{
					if (input(x, y, c) == 255) mask(x, y) = (1, 0);
					else if (input(x, y, c) == 0) mask(x, y) = (0, 0);
				}
			}
		}
		for (int i = 0; i < mask_rows; ++i)
		{
			for (int j = 0; j < mask_cols; ++j)
			{
				if ((sqrt((i - rows / 2)*(i - rows / 2) + (j - cols / 2)*(j - cols / 2))) < bandsize)	mat1(i, j) *= complex<double>(0, 0);
				else mat1(i, j) *= mask(i, j);
			}
		}
		for (int i = 0; i < mask_rows; ++i)
		{
			for (int j = 0; j < mask_cols; ++j)
			{
				if ((sqrt((i - rows / 2)*(i - rows / 2) + (j - cols / 2)*(j - cols / 2))) < bandsize)	mat2(i, j) *= complex<double>(0, 0);
				else mat2(i, j) *= mask(i, j);
			}
		}
		for (int i = 0; i < mask_rows; ++i)
		{
			for (int j = 0; j < mask_cols; ++j)
			{
				if ((sqrt((i - rows / 2)*(i - rows / 2) + (j - cols / 2)*(j - cols / 2))) < bandsize)	mat3(i, j) *= complex<double>(0, 0);
				else mat3(i, j) *= mask(i, j);
			}
		}
		mat1(rows / 2, cols / 2) = spectral_component1;
		mat2(rows / 2, cols / 2) = spectral_component2;
		mat3(rows / 2, cols / 2) = spectral_component3;
		mats_ptr->push_back(mat1);
		mats_ptr->push_back(mat2);
		mats_ptr->push_back(mat3);
		return mats_ptr;
	}
	

	unique_ptr<vector<matrix<complex<double>>>> FrequencyFiltrationUtils::PhaseModFilter(vector<matrix<complex<double>>>& mats, int k, int l)
	{
		unique_ptr<vector<matrix<complex<double>>>> mats_ptr(new vector<matrix<complex<double>>>());

		auto& mat = mats[0];
		const int rows = mat.size1();
		const int cols = mat.size2();

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				double x = (((-i * k * 2 * PI) / rows) + ((-j * l * 2 * PI) / cols) + (k + l) * PI);
				mat(i,j) *= complex<double>(cos(x), sin(x));
			}
		}
		mats_ptr->push_back(mat);
		return mats_ptr;
	}
}//core
}//imgproc