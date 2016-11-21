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
    static void createWindow(const std::string &name);
    static void show(core::Image &image, const std::string &window_name);
    static void closeWindow(const std::string &name);
    static void closeAll();
    /* wait for user action */
    static void wait();
};

} // opencv
} // imgproc

#endif // OPEN_CV_WINDOWS_
