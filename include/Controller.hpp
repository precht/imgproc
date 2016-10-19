/**
 *      Purpose:
 *          The main purpose for Controller class is to call proper operations on image due to
 *          passed arguments.
 *
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "img/Image.hpp"
#include <utility>
#include <vector>
#include <string>

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
const std::string DEFAULT_OUTPUT_NAME = "a.bmp";

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

  private:
    V_P_SS *arguments_;
};

} // namespace imgprocapp

#endif // CONTROLLER_HPP
