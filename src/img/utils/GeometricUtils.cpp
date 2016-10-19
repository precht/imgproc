/**
 *      Created:    18th Oct 2016
 *      Authors:    Jakub Precht
 */

#include "img/ImageCV.hpp"
#include "img/utils/GeometricUtils.hpp"
#include "img/utils/BasicUtils.hpp"

#include <iostream>

using namespace std;

namespace imgprocapp
{
namespace img
{
namespace utils
{

void GeometricUtils::flip_horizontally(Image *image)
{
    perform(image, 1, 0, -1, image->columns());
}

void GeometricUtils::flip_vertically(Image *image)
{
    perform(image, -1, image->rows(), 1, 0);
}

void GeometricUtils::flip_diagonally(Image *image)
{
    perform(image, -1, image->rows(), -1, image->columns());
}

void GeometricUtils::scale(Image *image, double times)
{
    if(times <= 0) throw "Wrong scaling value";
    perform(image, 1 / times, 0, 1 / times, 0, image->rows() * times, image->columns() * times);
}

void GeometricUtils::perform(Image *image, double ax, double bx, double ay, double by, 
        int size_x, int size_y)
{
    if(size_x < 0) size_x = image->rows();
    if(size_y < 0) size_y = image->columns();
    Image *tmp = new img::ImageCV(size_x, size_y, image->channels());

    for(int new_x = 0; new_x < size_x; ++new_x)
    {
        for(int new_y = 0; new_y < size_y; ++new_y)
        {
            // calculate old x axis (rows) coordinate
            int old_x = ax * new_x + bx;
            if(old_x < 0) old_x = 0;
            if(old_x >= image->rows()) old_x = image->rows() - 1;

            // calculate old y axis (columns) coordiante
            int old_y = ay * new_y + by;
            if(old_y < 0) old_y = 0;
            if(old_y >= image->columns()) old_y = image->columns() - 1;

            // copy pixels values
            for(int c = 0; c < image->channels(); ++c) 
            {
                *(tmp->ptr(new_x, new_y, c)) = *(image->ptr(old_x, old_y, c));
            }
        }
    }

    image->swap_content(tmp);
    delete tmp;
}

} // namespace utils 
} // namespace img
} // namespace imgprocapp

