#ifndef OPEN_CV_WINDOWS_
#define OPEN_CV_WINDOWS_

#include "core/Image.hpp"

#include <set>
#include <string>

namespace imgproc
{
namespace opencv
{

class OpenCVWindows
{
public:
    void createWindow(const std::string& name);
    void show(core::Image& image, const std::string& window_name);
    void closeWindow(const std::string& name);
    void closeAll();
    /* wait for user action */
    void wait();
    bool existWindow(const std::string& name);

private:
    std::set<std::string> windows_;
};

} // opencv
} // imgproc

#endif // OPEN_CV_WINDOWS_
