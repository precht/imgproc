/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#ifndef MORPHOLOGICAL_UTILS_HPP_
#define MORPHOLOGICAL_UTILS_HPP_

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"

namespace imgproc
{
namespace core
{

class MorphologicalUtils
{
public:
    static void dilation(Image& image, StructuralElement& element);
    static void erosion(Image& image, StructuralElement& element);
    static void opening(Image& image, StructuralElement& element);
    static void closing(Image& image, StructuralElement& element);
    // hit-and-miss transformation
    static void hmt(Image& image, StructuralElement& hit, StructuralElement& miss);

    // so far result unknown
    static void task6(Image& image);
};

} // core
} // imgproc

#endif // MORPHOLOGICAL_UTILS_HPP_
