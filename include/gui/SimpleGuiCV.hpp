/**
 *      Purpose:
 *          This class implements SimpleGui functionalities using OpenCV library, expecially
 *          highgui package.
 *
 *          WARNING: this class needs image to actually be ImageCV, because it will try to 
 *              cast it! 
 *
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#ifndef SIMPLE_GUI_CV_HPP 
#define SIMPLE_GUI_CV_HPP

#include "img/Image.hpp"
#include "gui/SimpleGui.hpp"

namespace imgprocapp
{
namespace gui
{

#define DEFAULT_WINDOW_NAME "imgprocapp"

class SimpleGuiCV : public SimpleGui
{
  public:
    SimpleGuiCV();
    ~SimpleGuiCV();
    void create_window();

    /* Careful, this methods will try to cast image to ImageCV */
    void show(img::Image &image);

    void close_window();

    /* wait for user action */
    void wait();
};

} // namespace gui
} // namespace imgprocapp

#endif // SIMPLE_GUI_CV_HPP
