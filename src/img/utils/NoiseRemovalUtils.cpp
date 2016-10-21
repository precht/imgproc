/**
 *      Created:    19th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
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

void NoiseRemovalUtils::geometric_mean_filter(Image *image, const int radius)
{
    perform_core(image, &perform_geometric_mean_filter, radius);
}

BYTE NoiseRemovalUtils::perform_geometric_mean_filter(std::vector<BYTE> &region, int)
{
    double product = 1;
    for(auto it = region.begin(); it != region.end(); ++it) product *= *it;

    int result = std::pow(product, 1.0 / region.size());
    if(result >= COLORS_NUMBER) result = COLORS_NUMBER - 1;
    assert(result >= 0); // power should never give negative number
    return (BYTE)result;
}

void NoiseRemovalUtils::alpha_trimmed_mean_filter(Image *image, const int alpha, const int radius)
{
    perform_core(image, &perform_alpha_trimmed_mean_filter, radius, alpha);
}

BYTE NoiseRemovalUtils::perform_alpha_trimmed_mean_filter(std::vector<BYTE> &region, const int alpha)
{
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

void NoiseRemovalUtils::perform_core(Image *image, BYTE(*filter)(std::vector<BYTE>&, const int), 
        const int radius, const int alpha)
{
    Image *tmp = new ImageCV(image->rows(), image->columns(), image->channels());
    std::vector<BYTE> region;

    const int rows = image->rows();
    const int columns = image->columns();
    const int channels = image->channels();
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
                    shift_x = (x + i) < 0 ? -(x + i) : 
                            (x + i) >= rows ? (rows - 1) - (x + i) : 0;
                    for(int j = -radius; j <= radius; ++j)
                    {
                        // detect row edge
                        shift_y = (y + j) < 0 ? -(y + j) : 
                                (y + j) >= columns ? (columns - 1) - (y + j) : 0;
                        region.push_back( *(image->ptr(x + i + shift_x, y + j + shift_y, c)));
                    }
                }
                *tmp->ptr(x, y, c) = filter(region, alpha);
            }
        }
    }

    image->swap_content(tmp);
    delete tmp;
}


} // namespace utils 
} // namespace img
} // namespace imgprocapp
