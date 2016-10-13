/**
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "image/Image.hpp"
#include "image/ImageCV.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace imgprocapp
{
namespace image
{

ImageCV::ImageCV(std::string input_name, std::string output_name)
    : Image(input_name, output_name)
{ }

ImageCV::ImageCV(ImageCV &&rval)
    : Image(std::move(rval))
    , data_matrix_(std::move(rval.data_matrix_))
{ }

ImageCV::~ImageCV()
{ }

bool ImageCV::load_image(std::string image_name)
{
    return false;
}

bool ImageCV::save_image(std::string image_name)
{
    return false;
}

size_t ImageCV::channels()
{
    return 0;
}

size_t ImageCV::rows()
{
    return 0;
}

size_t ImageCV::columns()
{
    return 0;
}

BYTE* ImageCV::at(size_t x, size_t y)
{
    return NULL;
}

} // namespace image
} // namespace imgprocapp

