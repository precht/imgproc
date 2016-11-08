



#ifndef NON_LINEAR_FILTRATION_UTILS_HPP_
#define NON_LINEAR_FILTRATION_UTILS_HPP_

#include "img/Image.hpp"
#include "img/Histogram.hpp"

namespace imgprocapp {
namespace img {
namespace utils {

class NonLinearFiltrationUtils
{
public:
	static void perform(Image *image);
	static void Uolis(Image *image);


};




}//namespace utils
}//namespace img
}//namespace imgprocapp
#endif