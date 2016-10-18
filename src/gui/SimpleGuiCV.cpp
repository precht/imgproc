/**
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#include "image/Image.hpp"
#include "image/ImageCV.hpp"
#include "gui/SimpleGui.hpp"
#include "gui/SimpleGuiCV.hpp"

#include <opencv2/highgui/highgui.hpp>

namespace imgprocapp
{
namespace gui
{

SimpleGuiCV::SimpleGuiCV()
{ }

SimpleGuiCV::~SimpleGuiCV()
{ }

void SimpleGuiCV::create_window()
{
    cv::namedWindow(DEFAULT_WINDOW_NAME, cv::WINDOW_AUTOSIZE);
}

void SimpleGuiCV::show(image::Image &image)
{
    image::ImageCV &image_cv = dynamic_cast<image::ImageCV&>(image);
    cv::imshow(DEFAULT_WINDOW_NAME, image_cv.get_Mat());
}

void SimpleGuiCV::close_window()
{
    cv::destroyWindow(DEFAULT_WINDOW_NAME);
}

void SimpleGuiCV::wait()
{
    cv::waitKey(0);
}

} // namespace gui
} // namespace imgprocapp


