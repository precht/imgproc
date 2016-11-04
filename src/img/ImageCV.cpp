/**
 *      Created:    12th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#include "img/Image.hpp"
#include "img/ImageCV.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iomanip>
#include <cassert>

namespace imgprocapp
{
namespace img
{

ImageCV::ImageCV()
{ }

ImageCV::ImageCV(int rows, int columns, int channels, ImageType type)
{
    if(type == unsigned_8bit)
    {
        if(channels == 1) data_matrix_.create(rows, columns, CV_8UC1);
        else if(channels == 2) data_matrix_.create(rows, columns, CV_8UC2);
        else if(channels == 3) data_matrix_.create(rows, columns, CV_8UC3);
        else throw "ImageCV: not supported channel numer";
    }
    else if(type == signed_16bit)
    {
        if(channels == 1) data_matrix_.create(rows, columns, CV_16SC1);
        else if(channels == 2) data_matrix_.create(rows, columns, CV_16SC2);
        else if(channels == 3) data_matrix_.create(rows, columns, CV_16SC3);
        else throw "ImageCV: not supported channel numer";
    }
    else assert(false);
}

// Create image that uses data instead of allocationg own memory (remember you have to delete data by yourself)
ImageCV::ImageCV(int rows, int columns, int channels, byte *data, ImageType type)
{
    cv::Mat *tmp = NULL;

    if(type == unsigned_8bit)
    {
        if(channels == 1) tmp = new cv::Mat(rows, columns, CV_8UC1, data);
        else if(channels == 2) tmp = new cv::Mat(rows, columns, CV_8UC2, data);
        else if(channels == 3) tmp = new cv::Mat(rows, columns, CV_8UC3, data);
        else throw "ImageCV: not supported channel numer";
    }
    else if(type == signed_16bit)
    {
        if(channels == 1) tmp = new cv::Mat(rows, columns, CV_16SC1, data);
        else if(channels == 2) tmp = new cv::Mat(rows, columns, CV_16SC2, data);
        else if(channels == 3) tmp = new cv::Mat(rows, columns, CV_16SC3, data);
        else throw "ImageCV: not supported channel numer";
    }
    else assert(false);

    cv::swap(data_matrix_, *tmp);
    delete tmp;
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
    if(data_matrix_.channels() > 3) throw "ImageCV: Input image has too many channels, not supported";
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

int ImageCV::channels() const
{
    return data_matrix_.channels();
}

int ImageCV::rows() const
{
    return data_matrix_.rows;
}

int ImageCV::columns() const
{
    return data_matrix_.cols;
}

void ImageCV::crop(int rows_from_start, int rows_from_end, int columns_from_start, int columns_from_end)
{
    int width = rows() - rows_from_start - rows_from_end;
    int hight = columns() - columns_from_start - columns_from_end;
    data_matrix_ = data_matrix_(cv::Rect(rows_from_start, columns_from_start, width, hight)).clone();
}

byte* ImageCV::ptr(int index) const
{
    int x = index / (columns() * channels());
    int y = index % (columns() * channels());
    return (byte*)data_matrix_.ptr<byte>(x) + y;
}

byte* ImageCV::ptr(int x, int y, int channel) const
{
    return (byte*)data_matrix_.ptr<byte>(x) + (y * channels()) + channel;
}

void ImageCV::print(std::ostream &where) const
{
    const int ch = channels();
    const int size_y = columns() * channels();
    const int size_total = size_y * rows();
    where << "{\n" << std::setw(4) << (int)(*ptr(0)) ;
    for(int i = 1; i < size_total; ++i)
    {
        if(i % size_y == 0) where << ",\n";
        else if(i % ch == 0) where << ",   ";
        else where << ",";
        where << std::setw(4) << (int)(*ptr(i)) ;
    }
    where << "\n}";
}

const cv::Mat& ImageCV::get_Mat()
{
    return data_matrix_;
}


} // namespace img
} // namespace imgprocapp

