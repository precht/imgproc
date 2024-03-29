/**
 *      Created:    4th Nov 2016
 *      Author:     Jakub Precht
 */

#ifndef CHARACTERISTIC_UTILS_HPP_
#define CHARACTERISTIC_UTILS_HPP_

#include "core/Image.hpp"
#include "core/Histogram.hpp"

#include <string>

namespace imgproc
{
namespace core
{

class CharacteristicUtils
{
  public:
    static const std::string all(const Histogram& h);
    static double mean(const Histogram& h);
    static double variance(const Histogram& h);
    static double standardDeviation(const Histogram& histogram);
    static double asymmetryCoefficient(const Histogram& histogram);
    static double flatteningCoefficient(const Histogram& histogram);
    static double variationCoefficient1(const Histogram& histogram);
    static double variationCoefficient2(const Histogram& histogram);
    static double informationSourceEntropy(const Histogram& histogram);
};


} // core
} // imgproc

#endif // CHARACTERISTIC_UTILS_HPP_
