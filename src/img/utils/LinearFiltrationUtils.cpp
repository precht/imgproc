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

void LinearFiltrationUtils::lineIdentification(Image *image)
{
    int mask[MASK_SIZE] = { 2, -1, -1, -1, 2, -1, -1, -1, 2 };
    perform(image, mask);
}

void LinearFiltrationUtils::perform(Image *image, int mask[MASK_SIZE])
{
    flipMask(mask);

    const int rows = image->rows();
    const int columns = image->columns();
    const int edge = MASK_EDGE / 2;
    int **table = new int*[rows];
    int max_val = INT_MIN;
    int min_val = INT_MAX;
    for (int i = 0 ; i < rows; ++i) table[i] = new int[columns]{0};

//    for(int k = 0; k < rows; k++)
//    {
//        for(int g = 0; g < columns; g++)
//           cout << (int)*image->ptr(k, g, 0) << "\t";
//        cout << endl;
//    }
//    cout << "---------------" << endl;

    for (int x = 0; x < rows; ++x)
    {
        for (int y = 0; y < columns; ++y)
        {
            for (int i = -edge; i <= edge; ++i)
            {
                if (x + i < 0 || x + i >= rows) continue;
                for (int j = -edge; j <= edge; ++j)
                {
                    if (y + j < 0 || y + j >= columns) continue;
                    table[x][y] += (int)(*image->ptr(x + i, y + j, 0) * mask[(i + 1) * 3 + (j + 1)]);
                }
            }
            if(table[x][y] > max_val) max_val = table[x][y];
            if(table[x][y] < min_val) min_val = table[x][y];
        }
    }
    cout << "MIN_MAX: " << min_val << " " << max_val << endl;

    // normalize colors and assign new values to image
    double scale = (double)255 / (max_val - min_val);
    int shift = -min_val;
    max_val = INT_MIN;
    min_val = INT_MAX;
    for (int x = 0; x < rows; ++x)
    {
        for (int y = 0; y < columns; ++y)
        {
            int r = scale * (table[x][y] + shift);
            if(r > max_val) max_val = r;
            if(r < min_val) min_val = r;
            *image->ptr(x, y, 0) = r;
        }
    }
    cout << "SCALE: " << scale << endl;
    cout << "MIN_MAX: " << min_val << " " << max_val << endl;
    for (int i = 0; i < image->rows(); ++i) delete table[i];
    delete table;
}

void LinearFiltrationUtils::flipMask(int mask[MASK_SIZE])
{
    int tmp[MASK_SIZE];
    std::memcpy(tmp, mask, sizeof(int) * MASK_SIZE);
    for(int i = 0; i < MASK_SIZE; ++i)
        mask[i] = tmp[MASK_SIZE - i - 1];
}

} // namespace utils
} // namespace img
} // namespace imgprocapp
