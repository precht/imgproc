/**
 *      Created:    20th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "opencv/OpenCVImageHelper.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdexcept>
#include <iostream>

using namespace std;

namespace imgproc
{
namespace opencv
{

bool OpenCVImageHelper::load(core::Image& image)
{
    cv::Mat mat = cv::imread(image.getInputName(), CV_LOAD_IMAGE_ANYCOLOR);
    if(mat.empty()) return false;
    const int a = mat.rows;
    const int b = mat.cols;
    const int c = mat.channels();
    image.resize(a, b, c);
    switch(c)
    {
    case 1:
    {
        cv::MatIterator_<unsigned char> it;
        const cv::MatIterator_<unsigned char> end = mat.end<unsigned char>();
        int p = 0;
        for(it = mat.begin<unsigned char>(); it != end; ++it)
            image(p++) = *it;
        break;
    }
    case 3:
    {
        cv::MatIterator_<cv::Vec3b> it;
        const cv::MatIterator_<cv::Vec3b> end = mat.end<cv:: Vec3b>();
        int p = 0;
        for(it = mat.begin<cv::Vec3b>(); it != end; ++it)
        {
            image(p++) = (*it)[0];
            image(p++) = (*it)[1];
            image(p++) = (*it)[2];
        }
        break;
    }
    default:
        std::runtime_error("cannot load image: unsupported number of channels, "
                               "can load only 1 and 3 channels");
    } // switch
    return true;
}

bool OpenCVImageHelper::save(core::Image& image)
{
    if(image.size() == 0) return false;
    const int a = image.rows();
    const int b = image.columns();
    const int c = image.channels();

    switch(c)
    {
    case 0:
        return false;
    case 1:
    {
        cv::Mat mat(a, b, CV_8UC1);
        cv::MatIterator_<unsigned char> it;
        const cv::MatIterator_<unsigned char> end = mat.end<unsigned char>();
        int p = 0;
        for(it = mat.begin<unsigned char>(); it != end; ++it)
            *it = image(p++);
        return  cv::imwrite(image.getOutputName(), mat);
    }
    case 3:
    {
        cv::Mat mat(a, b, CV_8UC3);
        cv::MatIterator_<cv::Vec3b> it;
        const cv::MatIterator_<cv::Vec3b> end = mat.end<cv:: Vec3b>();
        int p = 0;
        for(it = mat.begin<cv::Vec3b>(); it != end; ++it)
        {
            (*it)[0] = image(p++);
            (*it)[1] = image(p++);
            (*it)[2] = image(p++);
        }
        return  cv::imwrite(image.getOutputName(), mat);
    }
    default:
        std::runtime_error("cannot save image: unsupported number of channels, "
                                          "can save only 1 and 3 channels");
    } // switch
    return false;
}

} // opencv
} // imgproc

