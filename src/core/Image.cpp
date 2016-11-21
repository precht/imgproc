/**
 *      Created:    19th Nov 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"

#include <iomanip>
//#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>

namespace imgproc
{
namespace core
{

Image::Image()
    : rows_(0)
    , columns_(0)
    , channels_(0)
    , data_(nullptr)
    , helper_(nullptr)
    , input_name_("")
    , output_name_("")
{ }

Image::Image(std::shared_ptr<ImageHelper> helper, std::string input_name, std::string output_name_)
    : rows_(0)
    , columns_(0)
    , channels_(0)
    , data_(nullptr)
    , helper_(std::move(helper))
    , input_name_(std::move(input_name))
    , output_name_(std::move(output_name_))
{ }

Image::Image(int rows, int columns, int channels , std::shared_ptr<ImageHelper> helper,
             std::string input_name, std::string output_name)
    : rows_(rows)
    , columns_(columns)
    , channels_(channels)
    , data_(nullptr)
    , helper_(std::move(helper))
    , input_name_(std::move(input_name))
    , output_name_(std::move(output_name))
{
    if(rows_ < 0) throw std::invalid_argument("image rows cannot be negative");
    if(columns_ < 0) throw std::invalid_argument("image columns cannot be negative");
    if(channels_ < 0) throw std::invalid_argument("image channels cannot be negative");
    if(channels_ > MAX_CHANNELS) throw std::invalid_argument("image channels too big");
    data_ = new unsigned char[rows_ * columns_ * channels_]();
}

Image::Image(const unsigned char *data, int rows, int columns, int channels, std::shared_ptr<ImageHelper> helper,
             std::string input_name, std::string output_name)
    : Image(rows, columns, channels, std::move(helper), std::move(input_name), std::move(output_name))
{
    for(int i = 0; i < rows_ * columns_ * channels_; i++) data_[i] = data[i];
}

Image::Image(const Image& other)
    : rows_(other.rows_)
    , columns_(other.columns_)
    , channels_(other.channels_)
    , helper_(other.helper_)
    , input_name_(other.input_name_)
    , output_name_(other.output_name_)
{
    const int n = rows_ * columns_ * channels_;
    data_ = new unsigned char[n]();
    for(int i = 0; i < n; i++) data_[i] = other.data_[i];
//    std::cout << "Image(&)" << std::endl;
}

Image&Image::operator=(const Image& other)
{
//    std::cout << "Image=(&)" << std::endl;
    if(this != &other)
    {
        rows_ = other.rows_;
        columns_ = other.columns_;
        channels_ = other.channels_;
        helper_ = std::move(other.helper_);
        input_name_ = std::move(other.input_name_);
        output_name_ = std::move(other.output_name_);

        delete[] data_;
        data_ = new unsigned char[rows_ * columns_ * channels_]();
        const int n = rows_ * columns_ * channels_;
        for(int i = 0; i < n; i++) data_[i] = other.data_[i];
    }
    return *this;
}

Image::Image(Image &&other)
    : rows_(other.rows_)
    , columns_(other.columns_)
    , channels_(other.channels_)
    , data_(other.data_)
    , helper_(std::move(other.helper_))
    , input_name_(other.input_name_)
    , output_name_(other.output_name_)
{
    other.rows_ = 0;
    other.columns_ = 0;
    other.channels_ = 0;
    other.data_ = nullptr;
//    std::cout << "Image(&&)" << std::endl;
}

Image& Image::operator=(Image &&other)
{
//    std::cout << "Image=(&&)" << std::endl;
    if(this != &other)
    {
        delete[] data_;

        rows_ = other.rows_;
        columns_ = other.columns_;
        channels_ = other.channels_;
        data_ = other.data_;
        helper_ = std::move(other.helper_);
        input_name_ = std::move(other.input_name_);
        output_name_ = std::move(other.output_name_);

        other.rows_ = 0;
        other.columns_ = 0;
        other.channels_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

Image::~Image()
{
//    std::cout << "start destructing..." << std::endl;
    delete[] data_;
//    std::cout << "end destructing..." << std::endl;
}

int Image::rows() const
{
    return rows_;
}

int Image::columns() const
{
    return columns_;
}

int Image::channels() const
{
    return channels_;
}

int Image::size() const
{
    return rows_ * columns_ * channels_;
}

std::shared_ptr<ImageHelper> Image::getHelper() const
{
    return helper_;
}

void Image::setHelper(std::shared_ptr<ImageHelper> helper)
{
    helper_ = helper;
}

std::string Image::getInputName() const
{
    return input_name_;
}

void Image::setInputName(std::string input_name)
{
    input_name_ = std::move(input_name);
}

std::string Image::getOutputName() const
{
    return output_name_;
}

void Image::setOutputName(std::string output_name)
{
    output_name_ = std::move(output_name);
}

unsigned char& Image::operator()(int index)
{
    if(index < 0) throw std::out_of_range("image index cannot be negative");
    if(index >= rows_ * columns_ * channels_) throw std::out_of_range("image index has to be smaller then size");
    return data_[index];
}

unsigned char& Image::operator()(int row, int column, int channel)
{
    if(row < 0) throw std::out_of_range("image row cannot be negative");
    if(row >= rows_) throw std::out_of_range("image row has to be smaller then rows");
    if(column < 0) throw std::out_of_range("image column cannot be negative");
    if(column >= columns_) throw std::out_of_range("image column has to be smaller then columns");
    if(channel < 0) throw std::out_of_range("image channel cannot be negative");
    if(channel >= channels_) throw std::out_of_range("image channel has to be smaller then channels");
    return data_[(row * (columns_ * channels_)) + (column * channels_) + channel];
}

void Image::resize(int rows, int columns, int channels)
{
    rows_ = rows;
    columns_ = columns;
    channels_ = channels;
    delete[] data_;
    data_ = new unsigned char[rows_ * columns_ * channels_]();
}

bool Image::load()
{
    if(!helper_) throw std::logic_error("need to set helper before loading image");
    return helper_->load(*this);
}

bool Image::load(std::string name)
{
    if(!helper_) throw std::logic_error("need to set helper before loading image");
    input_name_ = std::move(name);
    return helper_->load(*this);
}

bool Image::save()
{
    if(!helper_) throw std::logic_error("need to set helper before saving image");
    return helper_->save(*this);
}

bool Image::save(std::string name)
{
    if(!helper_) throw std::logic_error("need to set helper before saving image");
    output_name_ = std::move(name);
    return helper_->save(*this);
}

void Image::crop(int rows_from_start, int rows_from_end, int columns_from_start, int columns_from_end)
{
    if(rows_from_start < 0 || rows_from_end < 0)
        throw std::invalid_argument("cannot crop negative number of rows");
    if(columns_from_start < 0 || columns_from_end < 0)
        throw std::invalid_argument("cannot crop negative number of columns");
    if(rows_from_start + rows_from_end > rows_)
        throw std::invalid_argument("cannot crop more rows than image has");
    if(columns_from_start + columns_from_end > columns_)
        throw std::invalid_argument("cannot crop more columns than image has");

    int new_rows = rows_ - rows_from_start - rows_from_end;
    int new_columns = columns_ - columns_from_start - columns_from_end;
    Image tmp = Image(new_rows, new_columns, channels_, helper_, input_name_, output_name_);
    for(int x = 0; x < new_rows; ++x)
        for(int y = 0; y < new_columns; ++y)
            for(int c = 0; c < channels_; c++)
                tmp(x, y, c) = this->operator()(x + rows_from_start, y + columns_from_start, c);
    this->swap(tmp);
}

void Image::swap(Image &other)
{
    Image tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
}

void Image::clear()
{
    rows_ = 0;
    columns_ = 0;
    channels_ = 0;
    delete[] data_;
    data_ = nullptr;
}

void Image::print(std::ostream &where) const
{
//    if(!size()) return;
    const int size_y = columns_ * channels_;
    const int size_total = size_y * rows_;
    where << "{";
    for(int i = 0; i < size_total; ++i)
    {
        if(i == 0) where << "\n";
        else if(i % size_y == 0) where << ",\n";
        else if(i % channels_ == 0) where << ",   ";
        else where << ",";
        where << std::setw(4) << (int)data_[i];
    }
    where << "\n}";
}

std::ostream& operator<<(std::ostream &out, const Image &image)
{
    image.print(out);
    return out;
}

} // core
} // imgproc

