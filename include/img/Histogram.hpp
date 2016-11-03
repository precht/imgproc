/**
 *      Purpose:
 *          This class stores histogram as an array, can calculate it from existing image and save to another image.
 *
 *      Created:    3rd Nov 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_

#include "Image.hpp"

namespace imgprocapp
{
namespace img
{


class Histogram
{
  public:
    Histogram();
    Histogram(Image &image);
    virtual ~Histogram();
    void createHistogram(Image &image);
    Image* saveAsImage();
    int getLevel(const int index) const;
    void setLevel(const int index, int value);
    int getLowestLevel() const;
    int getHighestLevel() const;
    int getPixels() const;

  private:
    int *values_ = NULL;
    int max_value_;
    int pixels_;
    int lowest_level_ = -1;
    int highest_level_ = -1;

    const static int SCALE = 2;
    const static byte WHITE = COLORS_NUMBER - 1;
    const static byte BLACK = 0;
};

} // namespace img
} // namespace imgprocapp


#endif // HISTOGRAM_HPP_

