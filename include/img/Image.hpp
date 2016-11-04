/**
 *      Purpose:
 *          Image is an abstract class, that allows other classes to be independent of a library
 *          used to read/write images from/to hdd. It provides simple methods to gain access to
 *          image matrix and modify values regardless of the Image's implementation.
 *
 *      Created:    12th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <string>
#include <ostream>

namespace imgprocapp
{
namespace img
{

#define DEBUG false
typedef unsigned char byte;
const int COLORS_NUMBER = 256;

enum ImageType{ unsigned_8bit, signed_16bit };

class Image
{
  public:
    Image();
    Image(std::string input_name, std::string output_name);
    virtual ~Image();
    virtual void load_image(const std::string &image_name) = 0;
    virtual void save_image(const std::string &image_name) = 0;
    virtual void swap_content(Image *other) = 0;

    // get image channels number
    virtual int channels() const = 0;

    // get image rows number
    virtual int rows() const = 0;

    // get image columns number
    virtual int columns() const = 0;

    // channel numbering starts with 0
    virtual byte* ptr(int index) const = 0;
    virtual byte* ptr(int x, int y, int channel) const = 0;

    void set_input_name(std::string input_name);
    void set_output_name(std::string output_name);

    // loads image using input_name
    void load_image();

    // saves image using output_name
    void save_image();

    // crop image specified number of pixels from each side
    virtual void crop(int rows_from_start, int rows_from_end, int columns_from_start, int columns_from_end) = 0;

    // we cannnot overload operator<<, thus it will use virtual print function
    virtual void print(std::ostream &where) const = 0;
    friend std::ostream& operator<<(std::ostream &out, const Image &image);

  private:
    std::string input_name_;
    std::string output_name_;
};

std::ostream& operator<<(std::ostream &out, const Image &image);

} // namespace img
} // namespace imgprocapp


#endif // IMAGE_HPP_

