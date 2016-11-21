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

StructuralElement::StructuralElement(int rows, int columns, int channels, int origin_row, int origin_column)
    : Image(rows, columns, channels)
    , origin_row_(origin_row)
    , origin_column_(origin_column)
{ }

int StructuralElement::getOriginRow() const
{
    return origin_row_;
}

void StructuralElement::setOriginRow(int origin_row)
{
    origin_row_ = origin_row;
}

int StructuralElement::getOriginColumn() const
{
    return origin_column_;
}

void StructuralElement::setOriginColumn(int origin_column)
{
    origin_column_ = origin_column;
}

//virtual StructuralElement::~StructuralElement();


} // core
} // imgproc
