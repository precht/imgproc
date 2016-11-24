/**
*      Created:    21th Nov 2016
*      Author:     Jakub Precht
*/

#ifndef STRUCTURAL_ELEMENT_HPP_
#define STRUCTURAL_ELEMENT_HPP_

#include "core/Image.hpp"

namespace imgproc
{
namespace core
{

class StructuralElement : public Image
{
public:
    // foreground color = Image::CHANNEL_MAX_VALUE tells which pixels should be considered
    // background color = 0 tells which pixels should be ignored

    StructuralElement();
    StructuralElement(int rows, int columns, int origin_row, int origin_column);
    StructuralElement(const unsigned char *data, int rows, int columns, int origin_row, int origin_column);
    virtual ~StructuralElement();

    int getOriginRow() const;
    int getOriginColumn() const;
    void setOriginRow(int origin_row);
    void setOriginColumn(int origin_column);

private:
    int origin_row_;
    int origin_column_;
};

} // core
} // imgproc

#endif // STRUCTURAL_ELEMENT_HPP_
