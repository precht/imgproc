/**
 *      Created:    19th Oct 2016
 *      Authors:    Jakub Precht
 */

#include "img/utils/NoiseRemovalUtils.hpp"
#include "img/ImageCV.hpp"

#include <cassert>
#include <algorithm>
#include <cmath>

namespace imgprocapp
{
namespace img
{
namespace utils
{

void NoiseRemovalUtils::geometric_mean_filter(Image *image, int radius)
{
    perform_core(image, &perform_geometric_mean_filter, radius);
}

BYTE NoiseRemovalUtils::perform_geometric_mean_filter(std::vector<BYTE> &region, unsigned)
{
    if(region.size() == 0) throw "Empty region"; // TODO

    double product = 1;
    for(auto it = region.begin(); it != region.end(); ++it) product *= *it;

    int result = std::pow(product, 1.0 / region.size());
    if(result >= COLORS_NUMBER) result = COLORS_NUMBER - 1;
    assert(result >= 0); // power should never give negative number
    return (BYTE)result;
}

void NoiseRemovalUtils::alpha_trimmed_mean_filter(Image *image, unsigned alpha, int radius)
{
    perform_core(image, &perform_alpha_trimmed_mean_filter, radius, alpha);
}

BYTE NoiseRemovalUtils::perform_alpha_trimmed_mean_filter(std::vector<BYTE> &region, unsigned alpha)
{
    if(alpha << 1 >= region.size()) throw "Alpha cannot be bigger than region size"; // TODO prop except

    // to perform faster for alpha equal 0 or 2 we don't need to sort region
    // instread find max and min value

    int sum = 0;
    int cut = 0;
    int min = COLORS_NUMBER;
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
    if(result >= COLORS_NUMBER) result = COLORS_NUMBER - 1;
    assert(result >= 0); // division of two positive numbers should give negative one
    return (BYTE)result;
}

void NoiseRemovalUtils::perform_core(Image *image, BYTE(*filter)(std::vector<BYTE>&, unsigned), 
        int radius, int alpha)
{
    if(radius < 0) radius = -radius;
    Image *tmp = new ImageCV(image->rows(), image->columns(), image->channels());
    std::vector<BYTE> region;

    // middle 
    for(int x = radius; x < image->rows() - 1; ++x)
    {
        for(int y = radius; y < image->columns() - 1; ++y)
        {
            for(int c = 0; c < image->channels(); ++c)
            {
                region.clear();
                for(int i = -radius; i <= radius; ++i)
                {
                    for(int j = -radius; j <= radius; ++j) region.push_back(*(image->ptr(x + i, y + j, c)));
                }
                *tmp->ptr(x, y, c) = filter(region, alpha);
            }
        }
    }

    // edges 
    for(int x = 0; x < image->rows(); ++x)
    {
        for(int c = 0; c < image->channels(); ++c)
        {
            *tmp->ptr(x, 0, c) = *(image->ptr(x, 0, c));
            *tmp->ptr(x, image->columns() - 1, c) = *(image->ptr(x, image->columns() - 1, c));
        }
    }
    for(int y = 0; y < image->rows(); ++y)
    {
        for(int c = 0; c < image->channels(); ++c)
        {
            *tmp->ptr(0, y, c) = *(image->ptr(0, y, c));
            *tmp->ptr(image->rows() - 1, y, c) = *(image->ptr(image->rows() - 1, y, c));
        }
    }

    image->swap_content(tmp);
    delete tmp;
}


} // namespace utils 
} // namespace img
} // namespace imgprocapp
