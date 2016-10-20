/**
 *      Created:    19th Oct 2016
 *      Authors:    Jakub Precht
 */

#include "img/Image.hpp"
#include "img/utils/ErrorMeasureUtils.hpp"

#include <cmath>
#include <cstdlib>
#include <cassert>

namespace imgprocapp
{
namespace img
{
namespace utils
{

int ErrorMeasureUtils::maximum_difference(Image *orginal, Image *changed)
{
    return perform(orginal, changed, ERROR_TYPE::MD);
}

double ErrorMeasureUtils::mean_square_error(Image *orginal, Image *changed)
{
    return perform(orginal, changed, ERROR_TYPE::MSE);
}

double ErrorMeasureUtils::peak_mean_square_error(Image *orginal, Image *changed)
{
    return perform(orginal, changed, ERROR_TYPE::PMSE);
}

double ErrorMeasureUtils::signal_to_noise_ratio(Image *orginal, Image *changed)
{
    return perform(orginal, changed, ERROR_TYPE::SNR);
}

double ErrorMeasureUtils::peak_signal_to_noise_ratio(Image *orginal, Image *changed)
{
    return perform(orginal, changed, ERROR_TYPE::PSNR);
}

double ErrorMeasureUtils::perform(Image *orginal, Image *changed, ERROR_TYPE type)
{
    // TODO prop except
    if(orginal->rows() != changed->rows() || orginal->columns() != changed->columns()) 
        throw "Incomparable images: different size";
    if(orginal->channels() != changed->channels())
        throw "Incomparable images: different channels number";

    int max_difference = 0;
    int orginal_max_value = 0;
    double orginal_square_sum = 0;
    double difference_square_sum = 0;

    for(int x = 0; x < orginal->rows(); ++x)
    {
        for(int y = 0; y < orginal->columns(); ++y)
        {
            for(int c = 0; c < orginal->channels(); ++c)
            {
                int orginal_val = *orginal->ptr(x, y, c); 
                int changed_val = *changed->ptr(x, y, c);

                // max original value
                if(orginal_val > orginal_max_value) orginal_max_value = orginal_val;
                // max difference
                int diff = std::abs(orginal_val - changed_val);
                if(diff > max_difference) max_difference = diff;
                // sums
                orginal_square_sum += std::pow(orginal_val, 2);
                difference_square_sum += std::pow(orginal_val - changed_val, 2);
            }
        }
    }
 
    double mse_val = difference_square_sum / (orginal->rows() * orginal->columns() 
            * orginal->channels());
    switch (type)
    {
        case MD:
            return max_difference;
        case MSE:
            return mse_val;
        case PMSE:
            return mse_val / std::pow(orginal_max_value, 2);
        case SNR:
            return 10 * std::log10(orginal_square_sum / difference_square_sum);
        case PSNR:
            return 10 * std::log10(std::pow(orginal_max_value, 2) / difference_square_sum);
        default:
            assert(false);
    }
}

} // namespace utils 
} // namespace img
} // namespace imgprocapp


