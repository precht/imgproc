/**
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "img/Image.hpp"

#include <iostream>

namespace imgprocapp
{
namespace img
{

Image::Image(int rows, int columns, int channels) 
{ }

Image::Image(std::string input_name, std::string output_name)
    : input_name_(input_name)
    , output_name_(output_name)
{ 
    if(DEBUG) std::cerr << "constructing Image(args)..." << std::endl;
}

Image::~Image()
{ 
    if(DEBUG) std::cerr << "destructing Image..." << std::endl;
}

void Image::set_input_name(std::string input_name)
{
    input_name_ = input_name;
}

void Image::set_output_name(std::string output_name)
{
    output_name_ = output_name;
}

void Image::load_image()
{
    load_image(input_name_);
}

void Image::save_image()
{
    save_image(output_name_);
}

} // namespace img
} // imgprocapp

