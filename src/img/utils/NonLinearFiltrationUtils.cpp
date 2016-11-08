#include <iostream>
#include <cmath>
#include <climits>
#include "img/utils/NonLinearFiltrationUtils.hpp"

namespace imgprocapp {
namespace img {
namespace utils {

void NonLinearFiltrationUtils::Uolis(Image &image)
{
    double numerator;
    double denominator;
    const int rows = image.rows();
    const int columns = image.columns();
    int **table = new int*[rows];
    int max_val = INT_MIN;
    int min_val = INT_MAX;
    for (int i = 0 ; i < rows; ++i) table[i] = new int[columns]{0};


    for (int i = 1; i < rows -1 ; i++)
    {
        for (int j = 1; j < columns - 1; j++)
        {
            numerator = pow(image(i,j,0) + 1, 4.0);
            denominator = (image(i - 1, j, 0) + 1) * (image(i, j + 1, 0) + 1) * (image(i + 1, j, 0) + 1) * (image(i, j - 1, 0) + 1);
            table[i][j] = 0.25 * log(numerator / denominator);
//            if(table[i][j] < 0) image(i, j, 0) = 0;
//            if(table[i][j] > 255) image(i, j, 0) = 255;
            if(table[i][j] > max_val) max_val = table[i][j];
            if(table[i][j] < min_val) min_val = table[i][j];
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

}//namespace utils
}//namespace img
}//namespace imgprocapp
