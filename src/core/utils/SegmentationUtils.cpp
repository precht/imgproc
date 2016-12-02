/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"
#include "core/utils/SegmentationUtils.hpp"

#include <stdexcept>
#include <queue>

namespace imgproc
{
namespace core
{

void SegmentationUtils::regionGrowing(Image& image, int seed_row, int seed_column,
                                      bool (*condition)(unsigned char, unsigned char, int, int),
                                      const int lower_condition_coefficient, const int higher_condition_coefficient,
                                      const StructuralElement& element)
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
    for(int i = 0; i < image.rows(); ++i)
		visited[i] = new bool[image.columns()]();

    const int lower = lower_condition_coefficient;
    const int higher = higher_condition_coefficient;
    const int origin_x = element.getOriginRow();
    const int origin_y = element.getOriginColumn();

    std::queue<std::pair<int, int>> seeds;

    if(condition(image(seed_row, seed_column, 0), image(seed_row, seed_column,  0), lower, higher))
    {
        seeds.push(std::make_pair(seed_row, seed_column));
        visited[seed_row][seed_column] = true;
    }

    while(!seeds.empty())
	{
        int seed_x = seeds.front().first;
        int seed_y = seeds.front().second;
        seeds.pop();
        tmp(seed_x, seed_y, 0) = Image::CHANNEL_MAX_VALUE;

        for(int a = 0; a < element.rows(); ++a)
        {
            for(int b = 0; b < element.columns(); ++b)
            {
                const int actual_x = seed_x + a - origin_x;
                if(actual_x < 0 || actual_x >= image.rows()) continue;
                const int actual_y =  seed_y + b - origin_y;
                if(actual_y < 0 || actual_y >= image.columns()) continue;

                const int seed_value = image(seed_x, seed_y, 0);
                const int candidate_value = image(actual_x, actual_y, 0);

                if(element.at(a, b, 0) && (!visited[actual_x][actual_y])
                        && (condition(seed_value, candidate_value, lower, higher)))
                {
                    seeds.push(std::make_pair(actual_x, actual_y));
                    visited[actual_x][actual_y] = true;
                }
            }
        }
	}

	for (int i = 0; i < image.rows(); ++i) delete[] visited[i];
	delete[] visited;
    image.swap(tmp);
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
    if(lower_delta < 0 || higher_delta < 0) throw std::invalid_argument("range growing delta cannot be negative");
    return (unsigned)(seed - candidate) <= (unsigned)lower_delta
            || (unsigned)(candidate - seed) <= (unsigned)higher_delta;
}

bool SegmentationUtils::rangeCondition(unsigned char, unsigned char candidate, int lower_value, int higher_value)
{
    return candidate >= lower_value && candidate <= higher_value;
}

const unsigned char SegmentationUtils::plus_se_data[]{
	0, X, 0,
	X, X, X,
	0, X, 0
};

const StructuralElement SegmentationUtils::plus_se(plus_se_data, 3, 3, 1, 1);



} // core
} // imgproc
