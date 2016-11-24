/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#ifndef MORPHOLOGICAL_UTILS_HPP_
#define MORPHOLOGICAL_UTILS_HPP_

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"

#include <utility>

namespace imgproc
{
namespace core
{

class MorphologicalUtils
{
public:
    static void erosion(Image& image, const StructuralElement& element = plus_se);
    static void dilation(Image& image, const StructuralElement& element = plus_se);
    static void opening(Image& image, const StructuralElement& element = plus_se);
    static void closing(Image& image, const StructuralElement& element = plus_se);
    // hit-and-miss transformation
    static void hmt(Image& image, const StructuralElement& hit, const StructuralElement& miss);

    // so far result unknown
    static void taskM6(Image& image);

private:
    // default "plus" shaped structural element
    static const unsigned char plus_se_data[];
    static const StructuralElement plus_se;
    // variables used for task m6, suffix _H means hit element, _M means miss element
    const static int TASK_M6_LOOPS_LIMIT = 1000;
    const static unsigned char X = Image::CHANNEL_MAX_VALUE;
    const static unsigned char A_H[];
    const static unsigned char A_M[];
    const static unsigned char B_H[];
    const static unsigned char B_M[];
    const static unsigned char C_H[];
    const static unsigned char C_M[];
    const static unsigned char D_H[];
    const static unsigned char D_M[];
    const static unsigned char E_H[];
    const static unsigned char E_M[];
    const static unsigned char F_H[];
    const static unsigned char F_M[];
    const static unsigned char G_H[];
    const static unsigned char G_M[];
    const static unsigned char H_H[];
    const static unsigned char H_M[];
    // the first element of the pair is the hit element, the second element is miss
    const static std::array<std::pair<StructuralElement, StructuralElement>, 8> elements;
};

} // core
} // imgproc

#endif // MORPHOLOGICAL_UTILS_HPP_
