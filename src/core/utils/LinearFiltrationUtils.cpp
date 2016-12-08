/**
*      Created:    4th Nov 2016
*      Author:     Jakub Precht
*/

#include "core/Image.hpp"
#include "core/Histogram.hpp"
//#include "core/utils/GeometricUtils.hpp"
#include "core/utils/LinearFiltrationUtils.hpp"

#include <cstring>
#include <climits>
//#include <iostream>
#include <cmath>

namespace imgproc
{
namespace core
{

const int LinearFiltrationUtils::LINE_IDENTIFICATION_MASK_1_[MASK_SIZE] = { -1, 2, -1, -1, 2, -1, -1, 2, -1 };
const int LinearFiltrationUtils::LINE_IDENTIFICATION_MASK_2_[MASK_SIZE] = { -1, -1, -1, 2, 2, 2, -1, -1, -1 };
const int LinearFiltrationUtils::LINE_IDENTIFICATION_MASK_3_[MASK_SIZE] = { -1, -1, 2, -1, 2, -1, 2, -1, -1 };
const int LinearFiltrationUtils::LINE_IDENTIFICATION_MASK_4_[MASK_SIZE] = { 2, -1, -1, -1, 2, -1, -1, -1, 2 };

void LinearFiltrationUtils::lineIdentification(Image& image)
{
    const int rows = image.rows();
    const int columns = image.columns();
    int max_val = INT_MIN;
    int min_val = INT_MAX;
    int **table = new int*[rows];
    for (int i = 0 ; i < rows; ++i) table[i] = new int[columns]();
    int accumulator = 0;

    for (int x = 1; x < rows - 1; ++x)
    {
        accumulator = 0;
        accumulator -= image(x - 1, 0, 0);
        accumulator -= image(x, 0, 0);
        accumulator -= image(x + 1, 0, 0);
        accumulator -= image(x - 1, 1, 0);
        accumulator -= image(x, 1, 0);
        accumulator -= image(x + 1, 1, 0);
        for (int y = 1; y < columns - 1; ++y)
        {
            accumulator -= image(x - 1, y + 1, 0);
            accumulator -= image(x, y + 1, 0);
            accumulator -= image(x + 1, y + 1, 0);

            table[x][y] = accumulator + 3 * (image(x-1, y-1, 0) + image(x, y, 0) + image(x+1, y+1, 0));
            if(table[x][y] > max_val) max_val = table[x][y];
            if(table[x][y] < min_val) min_val = table[x][y];

            accumulator += image(x - 1, y - 1, 0);
            accumulator += image(x, y - 1, 0);
            accumulator += image(x + 1, y - 1, 0);
        }
    }

    double scale = (double)255 / (max_val - min_val);
    int shift = -min_val;
    for (int x = 0; x < rows; ++x)
        for (int y = 0; y < columns; ++y)
            image(x, y, 0) = scale * (table[x][y] + shift);

    for (int i = 0; i < image.rows(); ++i) delete[] table[i];
    delete[] table;
}

void LinearFiltrationUtils::lineIdentification(Image& image, const int id)
{
    const int* mask;
    switch(id)
    {
    case 1: mask = LINE_IDENTIFICATION_MASK_1_; break;
    case 2: mask = LINE_IDENTIFICATION_MASK_2_; break;
    case 3: mask = LINE_IDENTIFICATION_MASK_3_; break;
    default: mask = LINE_IDENTIFICATION_MASK_4_; break;
    }
    perform(image, mask);
}

void LinearFiltrationUtils::perform(Image& image, const int mask[MASK_SIZE])
{
    const int rows = image.rows();
    const int columns = image.columns();
    const int half_edge = MASK_EDGE / 2;
    int max_val = INT_MIN;
    int min_val = INT_MAX;
    int **table = new int*[rows];
    for (int i = 0 ; i < rows; ++i) table[i] = new int[columns]();

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

    for (int i = 0; i < image.rows(); ++i) delete[] table[i];
    delete[] table;
}

} // core
} // imgproc
