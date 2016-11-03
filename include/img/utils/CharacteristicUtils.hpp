/**
 *      Purpose:
 *          Class contains different operations to measure image characterictics. (task 2)
 *
 *      Created:    4th Nov 2016
 *      Authors:  Jakub Precht
 */

#ifndef CHARACTERISTIC_UTILS_HPP_
#define CHARACTERISTIC_UTILS_HPP_

#include "img/Image.hpp"
#include "img/Histogram.hpp"

#include <string>

namespace imgprocapp
{
namespace img
{
namespace utils
{

class CharacteristicUtils
{
  public:
    static const std::string all(const Histogram &h);
    static double mean(const Histogram &h);
    static double variance(const Histogram &h);
    static double standardDeviation(const Histogram &histogram);
    static double asymmetryCoefficient(const Histogram &histogram);
    static double flatteningCoefficient(const Histogram &histogram);
    static double variationCoefficient1(const Histogram &histogram);
    static double variationCoefficient2(const Histogram &histogram);
    static double informationSourceEntropy(const Histogram &histogram);
};


} // namespace utils
} // namespace img
} // namespace imgprocapp

#endif // CHARACTERISTIC_UTILS_HPP_
