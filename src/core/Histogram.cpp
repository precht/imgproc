/**
*      Created:    3rd Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/Histogram.hpp"

namespace imgproc
{
namespace core
{

Histogram::Histogram()
    : values_(nullptr)
    , max_value_(0)
    , image_channel_size_(0)
    , lowest_level_(-1)
    , highest_level_(-1)
    , helper_(nullptr)
{ }

Histogram::~Histogram()
{
    delete[] values_;
}

void Histogram::create(Image &image)
{
    helper_ = image.getHelper();
    delete[] values_;

    values_ = new int[Image::CHANNEL_RANGE]();
    image_channel_size_ = image.rows() * image.columns();
    // TODO: color images, need to convert to hsv
    for (int x = 0; x < image.rows(); ++x)
        for (int y = 0; y < image.columns(); ++y)
            values_[image(x, y, 0)]++;

    max_value_ = 0;
    lowest_level_ = -1;
    highest_level_ = -1;
    for (int i = 0; i < Image::CHANNEL_RANGE; ++i)
    {
        if (values_[i] > max_value_) max_value_ = values_[i];
        if (lowest_level_ < 0 && values_[i]) lowest_level_ = i;
        if (values_[i]) highest_level_ = i;
    }
}

std::unique_ptr<Image> Histogram::toImage(int scale)
{
    if(image_channel_size_ == 0) return nullptr;

    int size = Image::CHANNEL_RANGE * scale;
    std::unique_ptr<Image> output(new Image(size, size, 1, helper_));
    // TODO do not use ImageCV constructor
    for (int y = 0; y < Image::CHANNEL_RANGE; ++y)
    {
        int val = Image::CHANNEL_RANGE - ((values_[y] * Image::CHANNEL_RANGE) / max_value_);
        for (int x = 0; x < Image::CHANNEL_RANGE; ++x)
        {
            for (int i = 0; i < SCALE; ++i)
                for (int j = 0; j < SCALE; ++j)
                    (*output)(x * scale + i, y * scale + j, 0) = x < val ? BACKGROUND : FOREGROUND;
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

int Histogram::getImageChannelSize() const
{
    return image_channel_size_;
}

} // namespace img
} // namespace imgprocapp
