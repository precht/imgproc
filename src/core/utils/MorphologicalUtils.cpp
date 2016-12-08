/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"
#include "core/utils/BasicUtils.hpp"
#include "core/utils/MorphologicalUtils.hpp"

#include <utility>
#include <iostream>
#include <array>
namespace imgproc
{
namespace core
{

void MorphologicalUtils::erosion(Image& image, const StructuralElement& element)
{
    const int origin_x = element.getOriginRow();
    const int origin_y = element.getOriginColumn();
    const int image_row_start = origin_x;
    const int image_column_start = origin_y;
    const int image_row_end =  image.rows() - (element.rows() - element.getOriginRow() - 1);
    const int image_column_end =  image.columns() - (element.columns() - element.getOriginColumn() - 1);

    Image tmp(image.rows(), image.columns(), image.channels(), image.getHelper(),
                 image.getInputName(), image.getOutputName());

    for(int x = image_row_start; x < image_row_end; ++x)
    {
        for(int y = image_column_start; y < image_column_end; ++y)
        {
            unsigned char color = Image::CHANNEL_MAX_VALUE;
            for(int a = 0; a < element.rows(); ++a)
                for(int b = 0; b < element.columns(); ++b)
                    if(element.at(a, b, 0)) color &= image(x + a - origin_x, y + b - origin_y, 0);
            tmp(x, y, 0) = color;
        }
    }
    image.swap(tmp);
}


void MorphologicalUtils::dilation(Image& image, const StructuralElement& element)
{
    const int origin_x = element.getOriginRow();
    const int origin_y = element.getOriginColumn();

    Image tmp(image.rows(), image.columns(), image.channels(), image.getHelper(),
              image.getInputName(), image.getOutputName());

    for(int x = 0; x < image.rows(); ++x)
    {
        for(int y = 0; y < image.columns(); ++y)
        {
            unsigned char color = 0;
            for(int a = 0; a < element.rows(); ++a)
            {
                for(int b = 0; b < element.columns(); ++b)
                {
                    if(element.at(a, b, 0))
                    {
                        const int actual_x = x + a - origin_x;
                        if(actual_x < 0 || actual_x >= image.rows()) continue;
                        const int actual_y = y + b - origin_y;
                        if(actual_y < 0 || actual_y >= image.columns()) continue;
                        color |= image(actual_x, actual_y, 0);
                    }
                }
            }
            tmp(x, y, 0) = color;
        }
    }
    image.swap(tmp);
}

void MorphologicalUtils::opening(Image& image, const StructuralElement& element)
{
    erosion(image, element);
    dilation(image, element);
}

void MorphologicalUtils::closing(Image& image, const StructuralElement& element)
{
    dilation(image, element);
    erosion(image, element);
}

// hit-and-miss transformation
void MorphologicalUtils::hmt(Image& image, const StructuralElement& hit, const StructuralElement& miss)
{
    Image tmp(image);
    erosion(image, hit);
    BasicUtils::negate(tmp);
    erosion(tmp, miss);
    for(int i = 0; i < image.size(); ++i) image(i) &= tmp(i);
}

void MorphologicalUtils::thickening(Image& image)
{
    Image saved;
    Image tmp;
    int loops = 1;
    do
    {
        saved = image;
        for(auto it : elements)
        {
            tmp = image;
            hmt(tmp, it.first, it.second);
            for(int i = 0; i < image.size(); ++i) image(i) |= tmp(i);
        }
//        if(loops % 10 == 0)
//            std::cout << loops << " loops..." << std::endl;
    }
    while ((saved != image) && (loops++ < THICKENING_LOOPS_LIMIT));
//    std::cout << "finished at loop " << loops << std::endl;
}

 // X = Image::CHANNEL_MAX_VALUE

const unsigned char MorphologicalUtils::plus_se_data[] {
    0, X, 0,
    X, X, X,
    0, X, 0
};

const StructuralElement MorphologicalUtils::plus_se(plus_se_data, 3, 3, 1, 1);

const unsigned char MorphologicalUtils::l_letter_hit_data[] {
    X, X, 0,
    0, X, 0,
    0, X, 0
};

const unsigned char MorphologicalUtils::l_letter_miss_data[] {
    0, 0, X,
    X, 0, X,
    X, 0, X
};

const StructuralElement MorphologicalUtils::l_letter_hit_se(l_letter_hit_data, 3, 3, 1, 1);
const StructuralElement MorphologicalUtils::l_letter_miss_se(l_letter_miss_data, 3, 3, 1, 1);

const unsigned char MorphologicalUtils::A_H[] {
    X, X, X,
    0, 0, 0,
    0, 0, 0
};
const unsigned char MorphologicalUtils::A_M[] {
    0, 0, 0,
    0, X, 0,
    X, X, X
};
const unsigned char MorphologicalUtils::B_H[] {
    0, X, X,
    0, 0, X,
    0, 0, 0
};
const unsigned char MorphologicalUtils::B_M[] {
    0, 0, 0,
    X, X, 0,
    X, X, 0
};
const unsigned char MorphologicalUtils::C_H[] {
    0, 0, X,
    0, 0, X,
    0, 0, X
};
const unsigned char MorphologicalUtils::C_M[] {
    X, 0, 0,
    X, X, 0,
    X, 0, 0
};
const unsigned char MorphologicalUtils::D_H[] {
    0, 0, 0,
    0, 0, X,
    0, X, X
};
const unsigned char MorphologicalUtils::D_M[] {
    X, X, 0,
    X, X, 0,
    0, 0, 0
};
const unsigned char MorphologicalUtils::E_H[] {
    0, 0, 0,
    0, 0, 0,
    X, X, X
};
const unsigned char MorphologicalUtils::E_M[] {
    X, X, X,
    0, X, 0,
    0, 0, 0
};
const unsigned char MorphologicalUtils::F_H[] {
    0, 0, 0,
    X, 0, 0,
    X, X, 0
};
const unsigned char MorphologicalUtils::F_M[] {
    0, X, X,
    0, X, X,
    0, 0, 0
};
const unsigned char MorphologicalUtils::G_H[] {
    X, 0, 0,
    X, 0, 0,
    X, 0, 0
};
const unsigned char MorphologicalUtils::G_M[] {
    0, 0, X,
    0, X, X,
    0, 0, X
};
const unsigned char MorphologicalUtils::H_H[] {
    X, X, 0,
    X, 0, 0,
    0, 0, 0
};
const unsigned char MorphologicalUtils::H_M[] {
    0, 0, 0,
    0, X, X,
    0, X, X
};

const std::array<std::pair<StructuralElement, StructuralElement>, 8> MorphologicalUtils::elements = {
    std::make_pair<StructuralElement, StructuralElement>(
            StructuralElement(A_H, 3, 3, 1, 1), StructuralElement(A_M, 3, 3, 1, 1)),
    std::make_pair<StructuralElement, StructuralElement>(
            StructuralElement(B_H, 3, 3, 1, 1), StructuralElement(B_M, 3, 3, 1, 1)),
    std::make_pair<StructuralElement, StructuralElement>(
            StructuralElement(C_H, 3, 3, 1, 1), StructuralElement(C_M, 3, 3, 1, 1)),
    std::make_pair<StructuralElement, StructuralElement>(
            StructuralElement(D_H, 3, 3, 1, 1), StructuralElement(D_M, 3, 3, 1, 1)),
    std::make_pair<StructuralElement, StructuralElement>(
            StructuralElement(E_H, 3, 3, 1, 1), StructuralElement(E_M, 3, 3, 1, 1)),
    std::make_pair<StructuralElement, StructuralElement>(
            StructuralElement(F_H, 3, 3, 1, 1), StructuralElement(F_M, 3, 3, 1, 1)),
    std::make_pair<StructuralElement, StructuralElement>(
            StructuralElement(G_H, 3, 3, 1, 1), StructuralElement(G_M, 3, 3, 1, 1)),
    std::make_pair<StructuralElement, StructuralElement>(
            StructuralElement(H_H, 3, 3, 1, 1), StructuralElement(H_M, 3, 3, 1, 1))
};

} // core
} // imgproc
