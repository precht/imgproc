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
    static const int FOREGROUND = Image::CHANNEL_RANGE - 1;
    static const int BACKGROUND = 0;

    StructuralElement(int rows, int columns, int channels, int origin_row, int origin_column);
    virtual ~StructuralElement();

    int getOriginRow() const;
    void setOriginRow(int origin_row);
    int getOriginColumn() const;
    void setOriginColumn(int origin_column);

private:
    int origin_row_;
    int origin_column_;
};

} // core
} // imgproc

#endif // STRUCTURAL_ELEMENT_HPP_
