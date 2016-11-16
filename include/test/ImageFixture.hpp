#ifndef IMAGE_FIXTURE_HPP_
#define IMAGE_FIXTURE_HPP_

#include "img/ImageCV.hpp"

#include <vector>

namespace imgprocapp{ namespace img {

struct DataSet
{
    imgprocapp::img::ImageCV &image;
    const int x;
    const int y;
    const int ch;
    const int size = x * y * ch;

    DataSet( imgprocapp::img::ImageCV &aImage, int aX, int aY, int aCh );
    virtual ~DataSet() = default;
};

class ImageFixture
{
public:
    std::vector<DataSet> data_sets_;

    static const int x0 = 2;
    static const int y0 = 2;
    static const int ch0 = 1;
    static const int size0 = x0 * y0 * ch0;
    static const int x1 = 2;
    static const int y1 = 2;
    static const int ch1 = 1;
    static const int size1 = x1 * y1 * ch1;
    static const int x2 = 4;
    static const int y2 = 3;
    static const int ch2 = 3;
    static const int size2 = x2 * y2 * ch2;
    static const imgprocapp::img::byte data0[];
    static const imgprocapp::img::byte data1[];
    static const imgprocapp::img::byte data2[];


    imgprocapp::img::ImageCV image0;
    imgprocapp::img::ImageCV image1;
    imgprocapp::img::ImageCV image2;

    ImageFixture();
    bool checkEqual( const imgprocapp::img::byte *data, int index, bool use_test_check = false );
    bool checkEqual( const imgprocapp::img::byte *data, imgprocapp::img::ImageCV &A,
                            int x, int y, int ch, bool use_test_check = false );
    virtual ~ImageFixture() = default;

private:
    imgprocapp::img::byte data0_copy[ size0 ];
    imgprocapp::img::byte data1_copy[ size1 ];
    imgprocapp::img::byte data2_copy[ size2 ];
};

} } // namespace
#endif // IMAGE_FIXTURE_HPP_
