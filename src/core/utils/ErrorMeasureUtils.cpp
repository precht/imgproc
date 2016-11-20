/**
 *      Created:    19th Oct 2016
 *      Authors:    Jakub Precht
 */

#include "core/Image.hpp"
#include "core/utils/ErrorMeasureUtils.hpp"

#include <cmath>
#include <cstdlib>
#include <cassert>

namespace imgproc
{
namespace core
{

int ErrorMeasureUtils::maximumDifference(Image& orginal, Image& changed)
{
    return perform(orginal, changed, ERROR_TYPE::MD);
}

double ErrorMeasureUtils::meanSquareError(Image& orginal, Image& changed)
{
    return perform(orginal, changed, ERROR_TYPE::MSE);
}

double ErrorMeasureUtils::peakMeanSquareError(Image& orginal, Image& changed)
{
    return perform(orginal, changed, ERROR_TYPE::PMSE);
}

double ErrorMeasureUtils::signalToNoiseRatio(Image& orginal, Image& changed)
{
    return perform(orginal, changed, ERROR_TYPE::SNR);
}

double ErrorMeasureUtils::peakSignalToNoiseRatio(Image& orginal, Image& changed)
{
    return perform(orginal, changed, ERROR_TYPE::PSNR);
}

double ErrorMeasureUtils::perform(Image& orginal, Image& changed, ERROR_TYPE type)
{
    if(orginal.rows() != changed.rows() || orginal.columns() != changed.columns())
        throw "Incomparable images: different size";
    if(orginal.channels() != changed.channels())
        throw "Incomparable images: different channels number";

    int max_difference = 0;
    int orginal_max_value = 0;
    double orginal_square_sum = 0;
    double difference_square_sum = 0;

    for(int x = 0; x < orginal.rows(); ++x)
    {
        for(int y = 0; y < orginal.columns(); ++y)
        {
            for(int c = 0; c < orginal.channels(); ++c)
            {
                int orginal_val = orginal(x, y, c);
                int changed_val = changed(x, y, c);

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

    double mse_val = difference_square_sum / (orginal.rows() * orginal.columns() * orginal.channels());
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

} // core
} // imgproc


