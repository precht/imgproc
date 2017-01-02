/**
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#include "core/Image.hpp"
#include "cli/Controller.hpp"
#include "cli/GuiController.hpp"
#include "opencv/OpenCVWindows.hpp"

namespace imgproc
{
namespace cli
{

//const std::string GuiController::IMAGE_WINDOW_NAME_ = "image";
//const std::string GuiController::HISTOGRAM_WINDOW_NAME_ = "histogram";

//GuiController::GuiController(V_P_SS *arguments)
//    : Controller(arguments)
//{ }

//void GuiController::run()
//{
//    bool show_histogram = false; // (image_.channels() == 1);
//    // image
//    windows_.createWindow(IMAGE_WINDOW_NAME_);
//    windows_.show(image_, IMAGE_WINDOW_NAME_);
//    // histogram
//    if(show_histogram)
//    {
//        windows_.createWindow(HISTOGRAM_WINDOW_NAME_);
//        windows_.show(*histogram_.toImage().get(), HISTOGRAM_WINDOW_NAME_);
//    }
//    // run operations
//    Controller::run();
//    windows_.wait();
//    // update windows
//    windows_.show(image_, IMAGE_WINDOW_NAME_);
//    if(show_histogram) windows_.show(*histogram_.toImage().get(), HISTOGRAM_WINDOW_NAME_);
//    windows_.wait();
//    // destroy windows
//    windows_.closeAll();
//}

} // cli
} // imgproc
