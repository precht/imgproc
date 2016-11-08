/**
*      Created:    4th Nov 2016
*      Author:  Jakub Precht
*/

#include "img/utils/LinearFiltrationUtils.hpp"
#include "img/utils/GeometricUtils.hpp"
#include "img/ImageCV.hpp"

#include <cstring>
#include <climits>
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

namespace imgprocapp {
namespace img {
namespace utils {


const int LinearFiltrationUtils::LINE_IDENTIFICATION_MASK_1_[MASK_SIZE] = { -1, 2, -1, -1, 2, -1, -1, 2, -1 };
const int LinearFiltrationUtils::LINE_IDENTIFICATION_MASK_2_[MASK_SIZE] = { -1, -1, -1, 2, 2, 2, -1, -1, -1 };
const int LinearFiltrationUtils::LINE_IDENTIFICATION_MASK_3_[MASK_SIZE] = { 2, -1, -1, -1, 2, -1, -1, -1, 2 };
const int LinearFiltrationUtils::LINE_IDENTIFICATION_MASK_4_[MASK_SIZE] = { -1, -1, 2, -1, 2, -1, 2, -1, -1 };

void LinearFiltrationUtils::lineIdentification(Image &image)
{
    const int *mask = LINE_IDENTIFICATION_MASK_4_;
    perform(image, mask);
}

void LinearFiltrationUtils::perform(Image &image, const int mask[MASK_SIZE])
{
    const int rows = image.rows();
    const int columns = image.columns();
    const int half_edge = MASK_EDGE / 2;
    int **table = new int*[rows];
    int max_val = INT_MIN;
    int min_val = INT_MAX;
    for (int i = 0 ; i < rows; ++i) table[i] = new int[columns]{0};

    for (int x = 0; x < rows; ++x)
    {
        for (int y = 0; y < columns; ++y)
        {
            for (int i = -half_edge; i <= half_edge; ++i)
            {
                if (x + i < 0 || x + i >= rows) continue;
                for (int j = -half_edge; j <= half_edge; ++j)
                {
                    if (y + j < 0 || y + j >= columns) continue;
                    table[x][y] += image(x + i, y + j, 0) * mask[(half_edge - i) * 3 + (half_edge - j)];
                }
            }
            if(table[x][y] > max_val) max_val = table[x][y];
            if(table[x][y] < min_val) min_val = table[x][y];
        }
    }

    double scale = (double)255 / (max_val - min_val);
    int shift = -min_val;
    for (int x = 0; x < rows; ++x)
        for (int y = 0; y < columns; ++y)
            image(x, y, 0) = scale * (table[x][y] + shift);

    for (int i = 0; i < image.rows(); ++i) delete table[i];
    delete table;
}


} // namespace utils
} // namespace img
} // namespace imgprocapp
