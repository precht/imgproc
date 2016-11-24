/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/StructuralElement.hpp"

namespace imgproc
{
namespace core
{

const int FOREGROUND = Image::CHANNEL_RANGE - 1;
const int BACKGROUND = 0;

StructuralElement::StructuralElement()
    : Image()
    , origin_row_(0)
    , origin_column_(0)
{ }

StructuralElement::StructuralElement(int rows, int columns, int origin_row, int origin_column)
    : Image(rows, columns, 1)
{
    setOriginRow(origin_row);
    setOriginColumn(origin_column);
}

StructuralElement::StructuralElement(const unsigned char* data, int rows, int columns,
                                     int origin_row, int origin_column)
    : Image(data, rows, columns, 1)
{
    setOriginRow(origin_row);
    setOriginColumn(origin_column);
}

StructuralElement::~StructuralElement()
{ }

int StructuralElement::getOriginRow() const
{
    return origin_row_;
}

int StructuralElement::getOriginColumn() const
{
    return origin_column_;
}

void StructuralElement::setOriginRow(int origin_row)
{
    if(origin_row < 0) throw std::invalid_argument("cannot set origin row smaller then 0");
    if(origin_row >= rows()) throw std::invalid_argument("origin row has to be smaller then rows number");
    origin_row_ = origin_row;
}

void StructuralElement::setOriginColumn(int origin_column)
{
    if(origin_column < 0) throw std::invalid_argument("cannot set origin column smaller then 0");
    if(origin_column >= columns()) throw std::invalid_argument("origin column has to be smaller then columns number");
    origin_column_ = origin_column;
}



} // core
} // imgproc
