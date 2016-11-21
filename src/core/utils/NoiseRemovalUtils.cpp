/**
 *      Created:    19th Oct 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "core/utils/NoiseRemovalUtils.hpp"

#include <cassert>
#include <algorithm>
#include <cmath>

namespace imgproc
{
namespace core
{

void NoiseRemovalUtils::geometricMeanFilter(Image& image, const int radius)
{
    perform(image, &geometricMeanFilterPerformer, radius);
}

unsigned char NoiseRemovalUtils::geometricMeanFilterPerformer(std::vector<unsigned char> &region, const int)
{
    double product = 1;
    for(auto it = region.begin(); it != region.end(); ++it) product *= *it;

    int result = std::pow(product, 1.0 / region.size());
    if(result >= Image::CHANNEL_RANGE) result = Image::CHANNEL_RANGE - 1;
    assert(result >= 0); // power should never give negative number
    return (unsigned char)result;
}

void NoiseRemovalUtils::alphaTrimmedMeanFilter(Image& image, const int alpha, const int radius)
{
    perform(image, &alphaTrimmedMeanFilterPerformer, radius, alpha);
}

unsigned char NoiseRemovalUtils::alphaTrimmedMeanFilterPerformer(std::vector<unsigned char> &region, const int alpha)
{
    // to perform faster for alpha equal 0 or 2 we don't need to sort region
    // instread find max and min value

    int sum = 0;
    int cut = 0;
    int min = Image::CHANNEL_RANGE;
    int max = -1;
    for(auto it = region.begin(); it != region.end(); ++it)
    {
        if(*it < min) min = *it;
        else if(*it > max) max = *it;
        sum += *it;
    }

    // if alpha == 0 do nothing, cut is 0
    if(alpha == 1) cut += min + max;
    else if(alpha > 1) 
    {
        std::sort(region.begin(), region.end());
        auto itb = region.begin();
        auto itr = region.rbegin();
        for(int i = alpha; i > 0; --i, ++itb, ++itr) cut += *itb + *itr;
    }

    int result = (double)(sum - cut) / (region.size() - (alpha << 1));
    if(result >= Image::CHANNEL_RANGE) result = Image::CHANNEL_RANGE - 1;
    assert(result >= 0); // division of two positive numbers should give negative one
    return (unsigned char)result;
}

void NoiseRemovalUtils::perform(Image& image, unsigned char(*filter)(std::vector<unsigned char>&, const int),
        const int radius, const int alpha)
{
    Image tmp(image);
    std::vector<unsigned char> region;

    const int rows = image.rows();
    const int columns = image.columns();
    const int channels = image.channels();
    // for detecting edges and shifting position, so values from middle are taken
    int shift_x = 0;
    int shift_y = 0;

    for(int x = 0; x < rows; ++x)
    {
        for(int y = 0; y < columns; ++y)
        {
            for(int c = 0; c < channels; ++c)
            {
                region.clear();
                for(int i = -radius; i <= radius; ++i)
                {
                    // detect column edge
                    shift_x = (x + i) < 0 ? -(x + i) : (x + i) >= rows ? (rows - 1) - (x + i) : 0;
                    for(int j = -radius; j <= radius; ++j)
                    {
                        // detect row edge
                        shift_y = (y + j) < 0 ? -(y + j) : (y + j) >= columns ? (columns - 1) - (y + j) : 0;
                        region.push_back(image((x + i + shift_x), (y + j + shift_y), c));
                    }
                }
                tmp(x, y, c) = filter(region, alpha);
            }
        }
    }
    image.swap(tmp);
}

} // core
} // imgproc
