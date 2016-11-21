/**
 *      Created:    20th Nov 2016
 *      Author:     Jakub Precht
 */

#ifndef OPEN_CV_IMAGE_HELPER_HPP
#define OPEN_CV_IMAGE_HELPER_HPP

#include "core/Image.hpp"

namespace imgproc
{
namespace opencv
{

struct OpenCVImageHelper : public core::ImageHelper
{
    bool load(core::Image& image) override;
    bool save(core::Image& image) override;
};

} // opencv
} // imgproc

#endif // OPEN_CV_IMAGE_HELPER_HPP
