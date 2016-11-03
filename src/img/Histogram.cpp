/**
*      Created:    3rd Nov 2016
*      Author(s):  Jakub Precht,
*                  Olek Winogradow
*/

#include "img/Histogram.hpp"
#include "img/ImageCV.hpp"

namespace imgprocapp
{
namespace img
{


Histogram::Histogram()
{ }

Histogram::Histogram(Image &image)
{
    createHistogram(image);
}

Histogram::~Histogram()
{
    if(values_ != NULL) delete values_;
}

void Histogram::createHistogram(Image &image)
{
    if(values_ != NULL) delete values_;
    values_ = new int[COLORS_NUMBER]{0};
    pixels_ = image.rows() * image.columns();
    for (int x = 0; x < image.rows(); ++x)
        for (int y = 0; y < image.columns(); ++y)
            // TODO color images, need to convert to hsv
            values_[*image.ptr(x, y, 0)]++;

    max_value_ = 0;
    lowest_level_ = -1;
    highest_level_ = COLORS_NUMBER;
    for (int i = 0; i < COLORS_NUMBER; ++i)
    {
        if (values_[i] > max_value_) max_value_ = values_[i];
        if (lowest_level_ < 0 && values_[i]) lowest_level_ = i;
        if (values_[i]) highest_level_ = i;
    }
}

Image* Histogram::saveAsImage()
{
    int output_size = COLORS_NUMBER * SCALE;
    Image *output = new ImageCV(output_size, output_size, 1);
    // TODO do not use ImageCV constructor
    for (int y = 0; y < COLORS_NUMBER; ++y)
    {
        int val = COLORS_NUMBER - ((values_[y] * COLORS_NUMBER) / max_value_);
        for (int x = 0; x < COLORS_NUMBER; ++x)
        {
            for (int i = 0; i < SCALE; ++i)
                for (int j = 0; j < SCALE; ++j)
                    *output->ptr(x * SCALE + i, y * SCALE + j, 0) = x < val ? WHITE : BLACK;
        }
    }
    return output;
}

int Histogram::getLevel(const int index) const
{
    return values_[index];
}

void Histogram::setLevel(const int index, int new_value)
{
    values_[index] = new_value;
}

int Histogram::getLowestLevel() const
{
    return lowest_level_;
}

int Histogram::getHighestLevel() const
{
    return highest_level_;
}

int Histogram::getPixels() const
{
    return pixels_;
}

} // namespace img
} // namespace imgprocapp
