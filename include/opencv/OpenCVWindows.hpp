/**
 *      Created:    21st Nov 2016
 *      Author:     Jakub Precht
 */

#ifndef OPEN_CV_WINDOWS_
#define OPEN_CV_WINDOWS_

#include "core/Image.hpp"

namespace imgproc
{
namespace opencv
{

class OpenCVWindows
{
public:
    void create_window(const std::string &name);
    void show(core::Image &image, const std::string &window_name);
    void close_window(const std::string &name);
    /* wait for user action */
    void wait();
};

} // opencv
} // imgproc

#endif // OPEN_CV_WINDOWS_
