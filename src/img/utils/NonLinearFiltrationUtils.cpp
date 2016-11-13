#include "img/utils/NonLinearFiltrationUtils.hpp"

#include <iostream>
#include <climits>
#include <cfloat>
#include <cmath>

namespace imgprocapp {
namespace img {
namespace utils {

void NonLinearFiltrationUtils::Uolis(Image &image)
{
    double numerator;
    double denominator;
    const int rows = image.rows();
    const int columns = image.columns();
    double **table = new double*[rows];
    double max_val = 0;
    double min_val = 0;
    for (int i = 0 ; i < rows; ++i) table[i] = new double[columns]{0};
    max_val = DBL_MIN;
    min_val = DBL_MAX;

    for (int i = 1; i < rows -1 ; i++)
    {
        for (int j = 1; j < columns - 1; j++)
        {
            numerator = pow((double)image(i,j,0) + 1, 4.0);
            denominator = (double)(image(i - 1, j, 0) + 1) * (image(i, j + 1, 0) + 1) * (image(i + 1, j, 0) + 1) * (image(i, j - 1, 0) + 1);
            table[i][j] = log10(numerator / denominator);
            if(table[i][j] > max_val) max_val = table[i][j];
            if(table[i][j] < min_val) min_val = table[i][j];
        }
    }

    double scale = (double)255 / (max_val - min_val);
    double shift = -min_val;
    for (int x = 0; x < rows; ++x)
        for (int y = 0; y < columns; ++y)
            image(x, y, 0) = scale * (table[x][y] + shift);

    for (int i = 0; i < image.rows(); ++i) delete table[i];
    delete table;
}

}//namespace utils
}//namespace img
}//namespace imgprocapp
