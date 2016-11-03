/**
*      Created:    4th Nov 2016
*      Authors:  Jakub Precht
*/

#include "img/utils/CharacteristicUtils.hpp"

#include <sstream>
#include <cmath>

namespace imgprocapp
{
namespace img
{
namespace utils
{


const std::string CharacteristicUtils::all(const Histogram &histogram)
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

double CharacteristicUtils::mean(const Histogram &histogram)
{
    int sum = 0;
    for (int i = 0; i < COLORS_NUMBER; ++i)
        sum += i * histogram.getLevel(i);
    return (double)sum / histogram.getPixels();
}

double CharacteristicUtils::variance(const Histogram &histogram)
{
    double m = mean(histogram);
    double sum = 0;
    for (int i = 0; i < COLORS_NUMBER; ++i)
        sum += pow(i - m, 2) * histogram.getLevel(i);
    return sum / histogram.getPixels();
}

double CharacteristicUtils::standardDeviation(const Histogram &histogram)
{
    return sqrt(variance(histogram));
}

double CharacteristicUtils::asymmetryCoefficient(const Histogram &histogram)
{
    double m = mean(histogram);
    double sd = standardDeviation(histogram);
    double sum = 0;
    for (int i = 0; i < COLORS_NUMBER; ++i)
        sum += pow(i - m, 3) * histogram.getLevel(i);
    return sum / pow(sd, 3) / histogram.getPixels();
}

double CharacteristicUtils::flatteningCoefficient(const Histogram &histogram)
{
    double m = mean(histogram);
    double sd = standardDeviation(histogram);
    double sum = 0;
    for (int i = 0; i < COLORS_NUMBER; ++i)
        sum += pow(i - m, 4) * histogram.getLevel(i) - 3;
    return sum / pow(sd, 4) / histogram.getPixels();
}

double CharacteristicUtils::variationCoefficient1(const Histogram &histogram)
{
    return standardDeviation(histogram) / mean(histogram);
}

double CharacteristicUtils::variationCoefficient2(const Histogram &histogram)
{
    double sum = 0;
    for (int i = 0; i < COLORS_NUMBER; ++i)
        sum += pow(histogram.getLevel(i), 2);
    return sum / pow(histogram.getPixels(), 2);
}

double CharacteristicUtils::informationSourceEntropy(const Histogram &histogram)
{
    double sum = 0;
    for (int i = 0; i < COLORS_NUMBER; ++i)
        if(histogram.getLevel(i))
            sum += histogram.getLevel(i) * log2((double)histogram.getLevel(i) / histogram.getPixels());
    return -sum / histogram.getPixels();
}


} // namespace utils
} // namespace img
} // namespace imgprocapp

