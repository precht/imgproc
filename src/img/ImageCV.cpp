/**
 *      Created:    12th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#include "img/Image.hpp"
#include "img/ImageCV.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace imgprocapp
{
namespace img
{

ImageCV::ImageCV()
{ }

ImageCV::ImageCV(int rows, int columns, int channels)
    : Image(rows, columns, channels)
{
    if(channels == 1) data_matrix_.create(rows, columns, CV_8UC1);
    else if(channels == 2) data_matrix_.create(rows, columns, CV_8UC2);
    else if(channels == 3) data_matrix_.create(rows, columns, CV_8UC3);
    else throw "ImageCV: not supported channel numer";
}

ImageCV::ImageCV(std::string input_name, std::string output_name)
    : Image(input_name, output_name)
{ 
    load_image(input_name);
}

ImageCV::~ImageCV()
{ 
    data_matrix_.release();
}

void ImageCV::load_image(const std::string& image_name)
{
    if(!data_matrix_.empty()) data_matrix_.release();
    data_matrix_ = cv::imread(image_name, CV_LOAD_IMAGE_ANYCOLOR);
    if(data_matrix_.empty()) throw "ImageCV: Failed to load image, probably wrong name";
    if(!data_matrix_.isContinuous()) 
    {
        // if image is not continous in memory try to reallocate (opencv tip)
        cv::Mat tmp = data_matrix_.clone();
        if(!tmp.isContinuous()) 
            throw "ImageCV: Image is not continuous, not supported";
        cv::swap(data_matrix_, tmp);
        tmp.release();
    }
}

void ImageCV::save_image(const std::string& image_name)
{
    cv::imwrite(image_name, data_matrix_);
}

void ImageCV::swap_content(Image *other)
{
    ImageCV *other_cv = dynamic_cast<img::ImageCV*>(other);
    if (other_cv == NULL) throw "Failed to cast Image to ImageCV";
    cv::swap(data_matrix_, other_cv->data_matrix_);
}

int ImageCV::channels()
{
    return data_matrix_.channels();
}

int ImageCV::rows()
{
    return data_matrix_.rows;
}

int ImageCV::columns()
{
    return data_matrix_.cols;
}

BYTE* ImageCV::ptr(int x, int y, int channel)
{
    return data_matrix_.ptr<BYTE>(x) + (y * data_matrix_.channels()) + channel;
}

const cv::Mat& ImageCV::get_Mat()
{
    return data_matrix_;
}


} // namespace img
} // namespace imgprocapp

