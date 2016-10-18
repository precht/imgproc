/**
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "image/Image.hpp"
#include "image/ImageCV.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// TODO delete debug cerrs
#include <iostream>

namespace imgprocapp
{
namespace image
{

ImageCV::ImageCV(std::string input_name, std::string output_name)
    : Image(input_name, output_name)
{ 
    if(DEBUG) std::cerr << "constructing ImageCV(args)..." << std::endl; 
    load_image(input_name);
}

ImageCV::~ImageCV()
{ 
    if(DEBUG) std::cerr  << "destructing ImageCV..." << std::endl;
    data_matrix_.release();
}

void ImageCV::load_image(const std::string& image_name)
{
    if(!data_matrix_.empty()) data_matrix_.release();
    if(DEBUG) std::cerr << "loading_image(name) ImageCV..." << std::endl;
    data_matrix_ = cv::imread(image_name, CV_LOAD_IMAGE_ANYCOLOR);
    // TODO porper exceptions
    if(data_matrix_.empty()) throw "ImageCV: Failed to load image, probably wrong name";
    if(!data_matrix_.isContinuous()) throw "ImageCV: Image is not continuous, not supported  ";
}

void ImageCV::save_image(const std::string& image_name)
{
    if(DEBUG) std::cerr << "saving_image(name) ImageCV..." << std::endl;
    cv::imwrite(image_name, data_matrix_);
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

BYTE* ImageCV::ptr(int x, int y, size_t channel)
{
    if(channel >= data_matrix_.channels()) throw "ImageCV::ptr: Wrong channel number!";
    return data_matrix_.ptr<BYTE>(x) + (y * data_matrix_.channels()) + channel;
}

const cv::Mat& ImageCV::get_Mat()
{
    return data_matrix_;
}


} // namespace image
} // namespace imgprocapp

