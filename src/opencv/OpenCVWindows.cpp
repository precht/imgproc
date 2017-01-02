#include "core/Image.hpp"
#include "opencv/OpenCVWindows.hpp"

#include <opencv2/highgui/highgui.hpp>

namespace imgproc
{
namespace opencv
{

void OpenCVWindows::createWindow(const std::string& name)
{
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    windows_.insert(name);
}

void OpenCVWindows::show(core::Image &image, const std::string& window_name)
{
    if(image.size() == 0) return;
    const int a = image.rows();
    const int b = image.columns();
    const int c = image.channels();

    cv::Mat *mat = nullptr;
    switch(c)
    {
    case 0:
        break;
    case 1:
    {
        mat = new cv::Mat(a, b, CV_8UC1);
        cv::MatIterator_<unsigned char> it;
        const cv::MatIterator_<unsigned char> end = mat->end<unsigned char>();
        int p = 0;
        for(it = mat->begin<unsigned char>(); it != end; ++it)
            *it = image(p++);
        break;
    }
    case 3:
    {
        mat = new cv::Mat(a, b, CV_8UC3);
        cv::MatIterator_<cv::Vec3b> it;
        const cv::MatIterator_<cv::Vec3b> end = mat->end<cv:: Vec3b>();
        int p = 0;
        for(it = mat->begin<cv::Vec3b>(); it != end; ++it)
        {
            (*it)[0] = image(p++);
            (*it)[1] = image(p++);
            (*it)[2] = image(p++);
        }
        break;
    }
    default:
        delete mat;
        std::runtime_error("cannot display image: unsupported number of channels, can display only 1 and 3 channels");
    } // switch

    cv::imshow(window_name, *mat);
    delete mat;
}

void OpenCVWindows::closeAll()
{
    cv::destroyAllWindows();
    windows_.clear();
}

void OpenCVWindows::closeWindow(const std::string& name)
{
    cv::destroyWindow(name);
    windows_.erase(windows_.find(name));
}

void OpenCVWindows::wait()
{
    cv::waitKey(0);
}

bool OpenCVWindows::existWindow(const std::string& name)
{
    return windows_.count(name);
}

} // opencv
} // imgproc


