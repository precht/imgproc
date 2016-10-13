/**
 *      Purpose:
 *          Image is an abstract class, that allows other classes to be independent of a library
 *          used to read/write images from/to hdd. It provides simple methods to gain access to
 *          image matrix and modify values regardless of the Image's implementation.
 *
 *      Created:    12th Oct 2016
 *      Autor:      Jakub Precht
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <memory>

namespace imgprocapp
{
namespace image
{

#define DEFAULT_OUTPUT_NAME "a.bmp"
typedef unsigned char BYTE;

class Image
{
  public:

    Image(std::string input_name, std::string output_name);
    Image(Image &&rval);
    virtual ~Image();

    virtual bool load_image(std::string image_name) = 0;
    virtual bool save_image(std::string image_name) = 0;

    /* get image channels number */
    virtual size_t channels() = 0;

    /* get image rows number */
    virtual size_t rows() = 0;

    /* get image columns number */
    virtual size_t columns() = 0;

    /* get pointer to matrix's element at position x, y */
    virtual BYTE* at(size_t x, size_t y) = 0;

    void set_input_name(std::string input_name);
    void set_output_name(std::string output_name);
    bool load_image();
    bool save_image();

  private:
    std::string input_name_;
    std::string output_name_;
};

typedef std::shared_ptr<Image> SPTR_IMG;

} // namespace image
} // namespace imgprocapp


#endif // IMAGE_HPP

