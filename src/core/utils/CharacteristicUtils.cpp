/**
*      Created:    4th Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/Histogram.hpp"
#include "core/utils/CharacteristicUtils.hpp"

#include <sstream>
#include <cmath>

namespace imgproc
{
namespace core
{

const std::string CharacteristicUtils::all(const Histogram& histogram)
{
    std::stringstream ss;
    ss << "mean: " << mean(histogram) << "\n";
    ss << "variance: " << variance(histogram) << "\n";
    ss << "standardDeviation: " << standardDeviation(histogram) << "\n";
    ss << "asymmetryCoefficient: " << asymmetryCoefficient(histogram) << "\n";
    ss << "flatteningCoefficient: " << flatteningCoefficient(histogram) << "\n";
    ss << "variationCoefficient1: " << variationCoefficient1(histogram) << "\n";
    ss << "variationCoefficient2: " << variationCoefficient2(histogram) << "\n";
    ss << "informationSourceEntropy: " << informationSourceEntropy(histogram) << "\n";
    return ss.str();
}

double CharacteristicUtils::mean(const Histogram& histogram)
{
    int sum = 0;
    for (int i = 0; i < Image::CHANNEL_RANGE; ++i)
        sum += i * histogram.getLevel(i);
    return (double)sum / histogram.getImageChannelSize();
}

double CharacteristicUtils::variance(const Histogram& histogram)
{
    double m = mean(histogram);
    double sum = 0;
    for (int i = 0; i < Image::CHANNEL_RANGE; ++i)
        sum += pow(i - m, 2) * histogram.getLevel(i);
    return sum / histogram.getImageChannelSize();
}

double CharacteristicUtils::standardDeviation(const Histogram& histogram)
{
    return sqrt(variance(histogram));
}

double CharacteristicUtils::asymmetryCoefficient(const Histogram& histogram)
{
    double m = mean(histogram);
    double sd = standardDeviation(histogram);
    double sum = 0;
    for (int i = 0; i < Image::CHANNEL_RANGE; ++i)
        sum += pow(i - m, 3) * histogram.getLevel(i);
    return sum / pow(sd, 3) / histogram.getImageChannelSize();
}

double CharacteristicUtils::flatteningCoefficient(const Histogram& histogram)
{
    double m = mean(histogram);
    double sd = standardDeviation(histogram);
    double sum = 0;
    for (int i = 0; i < Image::CHANNEL_RANGE; ++i)
        sum += pow(i - m, 4) * histogram.getLevel(i) - 3;
    return sum / pow(sd, 4) / histogram.getImageChannelSize();
}

double CharacteristicUtils::variationCoefficient1(const Histogram& histogram)
{
    return standardDeviation(histogram) / mean(histogram);
}

double CharacteristicUtils::variationCoefficient2(const Histogram& histogram)
{
    double sum = 0;
    for (int i = 0; i < Image::CHANNEL_RANGE; ++i)
        sum += pow(histogram.getLevel(i), 2);
    return sum / pow(histogram.getImageChannelSize(), 2);
}

double CharacteristicUtils::informationSourceEntropy(const Histogram& histogram)
{
    double sum = 0;
    for (int i = 0; i < Image::CHANNEL_RANGE; ++i)
        if(histogram.getLevel(i))
            sum += histogram.getLevel(i) * log2((double)histogram.getLevel(i) / histogram.getImageChannelSize());
    return -sum / histogram.getImageChannelSize();
}

} // core
} // imgproc
