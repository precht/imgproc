/**
 *      Purpose:
 *          The main purpose for Controller class is to call proper operations on image due to
 *          passed arguments.
 *
 *      Created:    13th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "core/core.hpp"

#include <utility>
#include <vector>
#include <string>

namespace imgproc
{
namespace cli
{

typedef std::pair<std::string, std::string> P_SS;
typedef std::vector<std::pair<std::string, std::string>> V_P_SS;

// TODO: change all
class Controller
{
public:
    // allocates new vector, puts there arguments and returns pointer to that vector,
    // you should release it's memory by yourself
    // input image name will be the first element
    // output name will be the second element
    static V_P_SS *read_arguments(int argc, char **argv);

    Controller(V_P_SS *arguments);
    virtual ~Controller();

    // performs operations on image due to passed arguments
    virtual void run();

protected:
    V_P_SS *arguments_;
    std::shared_ptr<core::ImageHelper> helper_ = nullptr;
    core::Image image_;
    core::Histogram histogram_;
};

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
const std::string SLINEID= "slineid";
const std::string UOLIS = "ouolis";
const std::string CALL = "call";
const std::string HISTOGRAM = "histogram";
const std::string CMEAN = "cmean";
const std::string CVARIANCE = "cvariance";
const std::string CSTDEV = "cstdev";
const std::string CVARCOI = "cvarcoi";
const std::string CASYCO = "casyco";
const std::string CFLATCO = "casyco";
const std::string CVARCOII = "cvarcoii";
const std::string CENTROPY = "centropy";
const std::string EROSION = "erosion";
const std::string DILATION = "dilation";
const std::string OPENING = "opening";
const std::string CLOSING = "closing";
const std::string HMT = "hmt";
const std::string THICKENING = "thickening";
const std::string DELTARG = "deltarg";
const std::string RANGERG = "rangerg";

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
"TASK3 PART\n"
"    The main aim was to become familiar with\n"
"    basic morphological operations and perform\n"
"    some variants of image segmentation\n"
"\n"
"    -erosion\n"
"        it perform erosion on 1-bit image\n"
"\n"
"    -dilation\n"
"        it perform dilation on 1-bit image\n"
"\n"
"    -opening\n"
"        it perform opening on 1-bit image\n"
"\n"
"    -closing\n"
"        it perform closing on 1-bit image\n"
"\n"
"    -hmt\n"
"        it perform hit-and-miss transformation on 1-bit image\n"
"\n"
"    -thickening\n"
"        it perform assigned task variant on 1-bit image\n"
"\n"
"    -deltarg=[lower_delta,higher_delta]\n"
"        it performs region growing, with criteria called by us delta condition\n"
"        you should insert both numbers from interval [0,255]\n"
"        delta condition works with respect to the following formula\n"
"        only those pixels will be joined into groups, which are included in interval\n"
"        [seed - lower_delta, seed + higher_delta], where seed is the intensity\n"
"        of pixel to which we are comparing another pixels\n"
"\n"
"    -rangerg\n"
"        it performs region growing, with criteria called by us range condition\n"
"        you should insert bout number from interval [0,255]\n"
"        first number indicate lower_value and second higher_value\n"
"        range condition works in the following way, lower and higher values\n"
"        indicates from which interval of intensity pixels will be joined into regions\n"
"TASK2 PART\n"
"\n"
"        creating an histogram of an image and displaying it\n"
"        if you want to have your histogram saved you should type in command line\n"
"        -histogram=[NameOfOutputFile]\n"
"        if you leave empty space after -histogram it will be saved as a_histogram.bmp\n "
"\n"
"    -huniform=[gmin,gmax]\n"
"        applying uniform final probability density function to histogram\n"
"        in order to improve the quality of the image\n"
"        gmin denotes minimum brightness in output image\n"
"        respectively gmax denotes maximum brightness in output image\n"
"\n"
"    -call\n"
"       this function invokes all image characteristics\n"
"       you need to type name of input file and after kind of image characteristic\n"
"      -in=[InputImageName] -call\n"
"\n"
"{\n"
"    -cmean\n"
"        comparing original image with the image\n"
"        after one of the quality improvement method\n"
"        in this case it is compared by mean\n"
"\n"
"    -cvariance\n"
"        comparing original image with the image\n"
"        after one of the quality improvement method\n"
"        in this case it is compared by variance\n"
"\n"
"    -cstdev\n"
"        comparing original image with the image\n"
"        after one of the quality improvement method\n"
"        in this case it is compared by standard deviation\n"
"\n"
"    -cvarcoi\n"
"        comparing original image with the image\n"
"        after one of the quality improvement method\n"
"        in this case it is compared by Variation coefficient 1\n"
"\n"
"    -casyco\n"
"        comparing original image with the image\n"
"        after one of the quality improvement method\n"
"        in this case it is compared by asymmetry coefficient\n"
"\n"
"    -cflatco\n"
"        comparing original image with the image\n"
"        after one of the quality improvement method\n"
"        in this case it is compared by flattening coefficient\n"
"\n"
"    -cvarcoii\n"
"        comparing original image with the image\n"
"        after one of the quality improvement method\n"
"        in this case it is compared by Variation coefficient 2\n"
"\n"
"    -centropy\n"
"        comparing original image with the image\n"
"        after one of the quality improvement method\n"
"        in this case it is compared by information source entropy\n"
"\n"
"}\n"
"    -slineid\n"
"        applying linear image filtration algorithm based on convolution\n"
"        in order to identify lines in our picture\n"
"        there are four types of masks which can be used with -slineid function\n"
"        each of them denote different lines orientation\n"
"        you have to type -slineid=[1-4] to choose the proper mask\n"
"        if left empty the fourth one will be chosen\n"
"\n"
"    -ouolis\n"
"        applying non-linear image filtration alghoritm \n"
"        in order to improve quality of the original image\n"
"\n"
"TASK1 PART\n"
"\n"
"    -histogram\n"
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

} // cli
} // imgprocapp

#endif // CONTROLLER_HPP_
