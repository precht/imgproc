/**
 *      Purpose:
 *          This class stores histogram as an array, can calculate it from existing image and save to another image.
 *
 *      Created:    3rd Nov 2016
 *      Author:     Jakub Precht
 */

#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_

#include "core/Image.hpp"

namespace imgproc
{
namespace core
{


class Histogram
{
  public:
    Histogram();
    virtual ~Histogram();

    int getLowestLevel() const;
    int getHighestLevel() const;
    int getImageChannelSize() const;
    int getLevel(const int index) const;
    void setLevel(const int index, int value);

    // create will earse previous data
    void create(Image&image);
    // returned image will have same halper as image in create method
    std::unique_ptr<Image> toImage(int scale = SCALE);

  private:
    const static int SCALE = 2;
    const static int FOREGROUND = 0;
    const static int BACKGROUND = Image::CHANNEL_RANGE - 1;

    int *values_;
    int max_value_;
    int image_channel_size_;
    int lowest_level_;
    int highest_level_;
    std::shared_ptr<ImageHelper> helper_;
};

} // namespace img
} // namespace imgprocapp


#endif // HISTOGRAM_HPP_

