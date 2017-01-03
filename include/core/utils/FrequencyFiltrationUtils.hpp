#ifndef FREQUENCY_FILTRATION_UTILS_HPP_
#define FREQUENCY_FILTRATION_UTILS_HPP_

#include "core/Image.hpp"
#include "core/utils/FrequencyUtils.hpp"
#include "opencv/OpenCVImageHelper.hpp"
#include <boost/numeric/ublas/matrix.hpp>

#include <complex>
#include <memory>
#include <vector>
#include <cmath>

using boost::numeric::ublas::matrix;
using std::complex;
using std::vector;
using std::unique_ptr;

enum TransformType { TT_ROW, TT_COLUMN };
enum ConvertType { CT_PHASE_MAGNITUDE, CT_REAL_IMAGINARY };

namespace imgproc
{
namespace core
{
class FrequencyFiltrationUtils	
{
public:
	static matrix<complex<double>> imageTOcomplex ( Image& input);
	static unique_ptr<vector<matrix<complex<double>>>> LowPassFilter (vector<matrix<complex<double>>>& mats, int bandsize);
	static unique_ptr<vector<matrix<complex<double>>>> HighPassFilter(vector<matrix<complex<double>>>& mats, int bandsize);
	static unique_ptr<vector<matrix<complex<double>>>> BandCutFilter(vector<matrix<complex<double>>>& mats, int min, int max);
	static unique_ptr<vector<matrix<complex<double>>>> HighPassWithEdgeDetFilter(vector<matrix<complex<double>>>& mats,int variant, int bandsize);
	static unique_ptr<vector<matrix<complex<double>>>> PhaseModFilter(vector<matrix<complex<double>>>& mats, int k, int l);

private:
	const static double PI;



};





} // core
} //imgproc
#endif