#include <iostream>
#include <cmath>
#include "img/utils/NonLinearFiltrationUtils.hpp"


namespace imgprocapp {
namespace img {
namespace utils {

void NonLinearFiltrationUtils::Uolis(Image* image)
{
	perform(image);
}
void NonLinearFiltrationUtils::perform(Image* image)
{
	byte *NEW = new byte;
	double numerator;
	double denominator;
	double ne;
	const int rows = image->rows();
	const int columns = image->columns();
	for (int i = 1; i < rows -1 ; i++)
	{
		for (int j = 1; j < columns - 1; j++)
		{
			numerator = pow(abs((int)(*image->ptr(i,j,0))) , 4.0);
			denominator = ((int)*image->ptr(i - 1, j, 0) * (int)*image->ptr(i, j + 1, 0) * (int)*image->ptr(i + 1, j, 0) * (int)*image->ptr(i, j - 1, 0));
			if (denominator == 0) ne = 0;
			else ne = ((1 / 4) * log(numerator / denominator));
			if (ne > 255) ne = 255;
			else if (ne < 0) ne = 0;
		    //*NEW = (byte)((1 / 4) * log(numerator / denominator));
			//*NEW = (1 / 4) * log(pow((double)(abs((int)image->ptr(i, j, 0))), 4.0) / ((int)image->ptr(i - 1, j, 0) * (int)image->ptr(i, j + 1, 0) * (int)image->ptr(i + 1, j, 0) * (int)image->ptr(i, j - 1, 0)));
			//if (*NEW > 255) *NEW = 255;
		    //else if (*NEW < 0) *NEW = 0;
			*NEW = (byte)ne;
			*image->ptr(i, j, 0) = *NEW;
	        std::cout << numerator << std::endl;
			std::cout << denominator << std::endl;
		}
	}
	
	delete NEW;
}

}//namespace utils
}//namespace img
}//namespace imgprocapp