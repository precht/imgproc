/**
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "image/Image.hpp"


namespace imgprocapp
{
namespace image
{

Image::Image(std::string input_name, std::string output_name)
    : input_name_(input_name)
    , output_name_(output_name)
{ }

Image::Image(Image &&rval)
    : input_name_(std::move(rval.input_name_))
    , output_name_(std::move(rval.output_name_))
{ }

Image::~Image()
{ }

void Image::set_input_name(std::string input_name)
{
    input_name_ = input_name;
}

void Image::set_output_name(std::string output_name)
{
    output_name_ = output_name;
}

bool Image::load_image()
{
    return load_image(input_name_);
}

bool Image::save_image()
{
    return save_image(output_name_);
}

} // namespace image
} // imgprocapp

