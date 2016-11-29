/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"
#include "core/utils/SegmentationUtils.hpp"

#include <stdexcept>
#include <cmath>
#include <queue>

namespace imgproc
{
namespace core
{

void SegmentationUtils::regionGrowing(Image& image, int seed_row, int seed_column,
                                      bool (*condition)(unsigned char, unsigned char, int, int),
                                      int lower_condition_coefficient, int higher_condition_coefficient, const StructuralElement& element)
{
    if(seed_row < 0) throw std::invalid_argument("seed row cannot be negative");
    if(seed_column < 0) throw std::invalid_argument("seed column cannot be negative");
    if(seed_row >= image.rows())
        throw std::invalid_argument("seed row has to be smaller then image rows number");
    if(seed_column >= image.columns())
        throw std::invalid_argument("seed column has to be smaller then image columns number");
	// TODO

	Image tmp(image.rows(), image.columns(), image.channels(), image.getHelper(),
		image.getInputName(), image.getOutputName());

	bool **visited = new bool *[image.rows()];
	for (int i = 0; i < image.rows(); ++i)
		visited[i] = new bool[image.columns()]();

	std::queue<std::pair<int, int>> que;

	que.push(std::make_pair(seed_row, seed_column));

	while (!que.empty())
	{
		int actual_x = que.front().first;
		int actual_y = que.front().second;
		que.pop();
		tmp(actual_x, actual_y, 0) = 255;
	//	visited[actual_x][actual_y] = true;
		if ((actual_x > 0) && (actual_x < image.rows() - 1) && (actual_y > 0) && (actual_y < image.columns() - 1))
		{
			for (int a = 0; a < element.rows(); ++a)
			{
				for (int b = 0; b < element.columns(); ++b)
				{
					if (element.at(a, b, 0) && (!visited[actual_x + a - 1][actual_y + b - 1]) && (deltaCondition(image(actual_x, actual_y, 0), image(actual_x + a - 1, actual_y + b - 1, 0), lower_condition_coefficient, higher_condition_coefficient)))
					{
						que.push(std::make_pair(actual_x + a - 1, actual_y + b - 1));
						visited[actual_x + a - 1][actual_y + b - 1] = true;
					}
				}
			}
		}
	}
	image.swap(tmp);
	for (int i = 0; i < image.rows(); ++i) delete[] visited[i];
	delete[] visited;
}

void SegmentationUtils::deltaRegionGrowing(Image& image, int seed_row, int seed_column,
                                           int lower_delta, int higher_delta,const StructuralElement& element)
{
    regionGrowing(image, seed_row, seed_column, deltaCondition, lower_delta, higher_delta, element);
}

void SegmentationUtils::rangeRegionGrowing(Image& image, int seed_row, int seed_column,
                                           int lower_value, int higher_value, const StructuralElement& element)
{
    regionGrowing(image, seed_row, seed_column, rangeCondition, lower_value, higher_value, element);
}

bool SegmentationUtils::deltaCondition(unsigned char seed, unsigned char candidate, int lower_delta, int higher_delta)
{
	if ((abs(seed - candidate) >= lower_delta) && (abs(seed - candidate) <= higher_delta)) return true;
    return false;
}

bool SegmentationUtils::rangeCondition(unsigned char seed, unsigned char candidate, int lower_value, int higher_value)
{
    // TODO
	//double distance = sqrt();
    return false;
}
const unsigned char SegmentationUtils::plus_se_data[]{
	0, X, 0,
	X, X, X,
	0, X, 0
};

const StructuralElement SegmentationUtils::plus_se(plus_se_data, 3, 3, 1, 1);



} // core
} // imgproc
