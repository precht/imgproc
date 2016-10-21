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

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

namespace imgprocapp
{
namespace img
{

#define DEBUG false
typedef unsigned char BYTE;
typedef BYTE* PIXEL[3];
const int COLORS_NUMBER = 256;

class Image
{
  public:
    Image();
    /* This constructor does not load any image, it only allocates empty space */
    Image(int rows, int columns, int channels);
    /* This constructor loads image */
    Image(std::string input_name, std::string output_name);
    virtual ~Image();
    virtual void load_image(const std::string &image_name) = 0;
    virtual void save_image(const std::string &image_name) = 0;
    virtual void swap_content(Image *other) = 0;

    /* get image channels number */
    virtual int channels() = 0;

    /* get image rows number */
    virtual int rows() = 0;

    /* get image columns number */
    virtual int columns() = 0;

    /* channel numbering starts with 0 */
    virtual BYTE* ptr(int x, int y, int channel) = 0;

    void set_input_name(std::string input_name);
    void set_output_name(std::string output_name);

    /* loads image using input_name */
    void load_image();

    /* saves image using output_name */
    void save_image();

  private:
    std::string input_name_;
    std::string output_name_;
};

} // namespace img
} // namespace imgprocapp


#endif // IMAGE_HPP

