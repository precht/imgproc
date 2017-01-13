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

enum TransformType { TT_ROW, TT_COLUMN };
enum ConvertType { CT_PHASE_MAGNITUDE, CT_REAL_IMAGINARY };

namespace imgproc
{
namespace core
{
class FrequencyFiltrationUtils	
{
public:
//    static boost::numeric::ublas::matrix<std::complex<double>> imageTOcomplex ( Image& input);
    static void lowPassFilter(std::vector<boost::numeric::ublas::matrix<std::complex<double>>>& mats, int bandsize);
    static void highPassFilter(std::vector<boost::numeric::ublas::matrix<std::complex<double>>>& mats, int bandsize);
    static void bandCutFilter(std::vector<boost::numeric::ublas::matrix<std::complex<double>>>& mats, int min, int max);
    static void highPassWithEdgeDetFilter(std::vector<boost::numeric::ublas::matrix<std::complex<double>>>& mats, int variant, int bandsize);
    static void phaseModFilter(std::vector<boost::numeric::ublas::matrix<std::complex<double>>>& mats, int k, int l);

private:
	const static double PI;



};





} // core
} //imgproc
#endif
