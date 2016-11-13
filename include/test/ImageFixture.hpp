#ifndef IMAGE_FIXTURE_HPP_
#define IMAGE_FIXTURE_HPP_

#include "img/ImageCV.hpp"

namespace imgprocapp {
namespace img {

class Image_F
{
public:
    static const int x1 = 2;
    static const int y1 = 2;
    static const int ch1 = 1;
    static const int size1 = x1 * y1 * ch1;
    static const int x2 = 3;
    static const int y2 = 2;
    static const int ch2 = 1;
    static const int size2 = x2 * y2 * ch2;
    static const int x3 = 4;
    static const int y3 = 3;
    static const int ch3 = 3;
    static const int size3 = x3 * y3 * ch3;
    static const imgprocapp::img::byte data1[];
    static const imgprocapp::img::byte data2[];
    static const imgprocapp::img::byte data3[];


    imgprocapp::img::ImageCV image1;
    imgprocapp::img::ImageCV image2;
    imgprocapp::img::ImageCV image3;

    Image_F();
    static bool check_if_different(imgprocapp::img::ImageCV &A, const imgprocapp::img::byte *data,
                                   int x, int y, int ch, bool use_test_check = false);
    virtual ~Image_F() = default;

private:
    imgprocapp::img::byte data1_copy[size1];
    imgprocapp::img::byte data2_copy[size2];
    imgprocapp::img::byte data3_copy[size3];
};

}
}
#endif // IMAGE_FIXTURE_HPP_
