/**
 *      Purpose:
 *          ImageCV is implementation of Image class that useses OpenCV as a helping library.
 *
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#ifndef IMAGE_CV_HPP
#define IMAGE_CV_HPP

#include "Image.hpp"
#include <opencv2/core/core.hpp>


namespace imgprocapp
{
namespace image
{

#define DEFAULT_OUTPUT_NAME "a.bmp"

class ImageCV : public Image
{
  public:

    /* intput_name must be provied,
     * output_name may be left empty and it will obtain default value */
    ImageCV(std::string intput_name, std::string output_name = DEFAULT_OUTPUT_NAME);
    ImageCV(ImageCV &&rval);

    ~ImageCV();
    bool load_image(std::string);
    bool save_image(std::string);
    size_t channels();
    size_t rows();
    size_t columns();
    BYTE* at(size_t x, size_t y);

    /* This function is meant for gui classes which want to dispaly image.
     * It is not recommended to use it to change values of image matrix
     * (although it is possible) because image may not be consistant. */
    const cv::Mat& get_Mat();

  private:
    cv::Mat data_matrix_;
};

} // namespace image
} // namespace imgprocapp


#endif // IMAGE_CV_HPP
