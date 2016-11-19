/**
 *      Purpose:
 *          ImageCV is implementation of Image class that useses OpenCV as a helping library.
 *
 *      Created:    12th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#ifndef IMAGE_CV_HPP_
#define IMAGE_CV_HPP_

#include "img/Image.hpp"

#include <opencv2/core/core.hpp>

namespace imgprocapp
{
namespace img
{

class ImageCV : public Image
{
  public:
    ImageCV();
    /* This constructor does not load any image, it only allocates empty space */
    ImageCV(int rows, int columns, int channels, ImageType type = unsigned_8bit);
    // Create image that uses data instead of allocationg own memory (remember you have to free data by yourself)
    ImageCV(int rows, int columns, int channels, byte *data, ImageType type = unsigned_8bit);
    /* output_name may be lest empty, it will obtain default value;
     * constructor does not load any image, you have to call load_image. */
    ImageCV(std::string intput_name, std::string output_name);

    ~ImageCV();

    /* loads image using input_name */
    void load_image(const std::string &image_name);

    /* saves image using output_name */
    void save_image(const std::string &image_name);

    /* swap image matrix with other image */
    void swap_content(Image *other);

    int channels() const;
    int rows() const;
    int columns() const;

    void crop(int rows_from_start, int rows_from_end, int columns_from_start, int columns_from_end);

    /* channel numbering starts with 0 */
    byte* ptr(int index) const;
    byte* ptr(int x, int y, int channel) const;
    byte& operator()(int index);
    byte& operator()(int x, int y, int c);

    void print(std::ostream &where) const;

    /* This function is meant for gui classes which want to dispaly image.
     * It is not recommended to use it to change values of image matrix
     * (although it is possible) because image may not be consistant. */
    const cv::Mat& get_Mat();

  private:
    cv::Mat data_matrix_;
};

} // namespace img
} // namespace imgprocapp


#endif // IMAGE_CV_HPP_
