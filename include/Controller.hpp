/**
 *      Purpose:
 *          The main purpose for Controller class is to call proper operations on image due to
 *          passed arguments.
 *
 *      Created:    13th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "img/Image.hpp"
#include <utility>
#include <vector>
#include <string>
#include "img/Histogram.hpp"

namespace imgprocapp
{

typedef std::pair<std::string, std::string> P_SS;
typedef std::vector<std::pair<std::string, std::string>> V_P_SS;
const std::string INPUT_NAME = "in";
const std::string OUTPUT_NAME = "out";
const std::string BRIGHTNESS = "brightness";
const std::string CONTRAST = "contrast";
const std::string NEGATIVE = "negative";
const std::string HORIZONTAL_FLIP = "hflip";
const std::string VERTICAL_FLIP = "vflip";
const std::string DIAGONAL_FLIP = "dflip";
const std::string SHRINK = "shrink";
const std::string ENLARGE = "enlarge";
const std::string GEOMETRIC_MEAN_FILTER = "gmean";
const std::string ALPHA_TRIMMED_MEAN_FILTER = "alpha";
const std::string MAXIMUM_DIFFERENCE = "md";
const std::string MEAN_SQUARE_ERROR = "mse";
const std::string PEAK_MEAN_SQUARE_ERROR = "pmse";
const std::string SIGNAL_NOISE_RATIO = "snr";
const std::string PEAK_SIGNAL_NOISE_RATIO = "psnr";
const std::string HELP = "help";
const std::string DEFAULT_OUTPUT_NAME = "a.bmp";
const std::string HUNIFORM = "huniform";

class Controller
{
  public:
    /* allocates new vector, puts there arguments and returns pointer to that vector,
     * you should release it's memory by yourself
     * input image name will be the first element 
     * output name will be the second element */
    static V_P_SS *read_arguments(int argc, char **argv);

    Controller(V_P_SS *arguments);
    virtual ~Controller();

    /* performs operations on image due to passed arguments */
    virtual void run();

  protected:
    img::Image *image_;
    img::Histogram histogram_;

  private:
    V_P_SS *arguments_;

};

const std::string HELP_CONTENT = "\n"
"NAME:\n"
"    Imgprocapp - An image processing library\n"
"\n"
"AUTHORS:\n"
"    Jakub Precht\n"
"    Olek Winogradow\n"
"\n"
"SYNOPSIS:\n"
"    (g)imgprocapp [-command=value [...]]\n"
"\n"
"DESCRIPTION:\n"
"    First of all, to specify input and output use -in  and -out options. \n"
"    Operations on image will be performed in the same order as options were\n"
"    passed (from left to right). Be careful to not put any spaces between =\n"
"    sign and values.\n"
"\n"
"    List of all possible options:\n"
"    \n"
"    -in=[input file]\n"
"        input image name\n"
"\n"
"    -out=[output file]\n"
"        output image name, if left empty image will be saved as a.bmp\n"
"\n"
"    -brightness=[shift]\n"
"        change image birghtness. shift can be both positive and negative but\n"
"        it's absolute value can not be greater then the number of image's \n"
"        posible colors (per channel) - usually it cannot be greater then 255\n"
"\n"
"    -contrast=[slope]\n"
"        change image contrast. slope can be any real number and it specifies\n"
"        function from X (orginal colors) to Y (new colors). the constant \n"
"        point of this function is color 127\n"
"\n"
"    -negative\n"
"        replace all image's colors with the oppoosite ones\n"
"\n"
"    -hflip\n"
"        flip image horizontally\n"
"        \n"
"    -vflip\n"
"        flip image vertically\n"
"\n"
"    -dflip\n"
"        flip image diagonally\n"
"\n"
"    -shrink=[times]\n"
"        shrink image specified times. times can be any real number greater\n"
"        then 1\n"
"    \n"
"    -enlarge=[times]\n"
"        enlarge image specified times. times can be any real number greater\n"
"        then 1\n"
"    \n"
"    -gmean\n"
"        remove noise using geometric mean filter. size of the rectangle \n"
"        used for calculations is 3x3\n"
"    \n"
"    -alpha=[drop]\n"
"        remove noise using alpha-trimmed mean filter. size of the rectangle\n"
"        used for calculations is 3x3. drop value specifies how many extreme\n"
"        values drop form each side before calculating new value. i.e.\n"
"        for drop=1 it drop 1 max value and 1 min value, so in total 2 values.\n"
"        thus cannot be greater then 4, for which this filter behaves like\n"
"        median filter\n"
"\n"
"    -md=[orginal file]\n"
"        compare maximum color difference (per channel) between loaded image \n"
"        and orginal \n"
"\n"
"    -mse=[orginal file]\n"
"        compare loaded image with orginal using mean square error method \n"
"\n"
"    -pmse=[orginal file]\n"
"        compare loaded image with orginal using peak mean square error method \n"
"\n"
"    -snr=[orginal file]\n"
"        compare loaded image with orginal using signal to noise ratio method \n"
"\n"
"    -psnr=[orginal file]\n"
"        compare loaded image with orginal using peak signal to noise ratio \n"
"        method \n"
"\n"
"    -help\n"
"        displays help message with all possible options\n"
"\n";

} // namespace imgprocapp

#endif // CONTROLLER_HPP
