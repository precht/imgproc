/**
 *      Created:    13th Oct 2016
 *      Author(s):  Jakub Precht
 */

#include "GuiController.hpp"
#include "gui/SimpleGuiCV.hpp"

namespace imgprocapp
{

const std::string GuiController::IMAGE_WINDOW_NAME_ = "image";
const std::string GuiController::HISTOGRAM_WINDOW_NAME_ = "histogram";

GuiController::GuiController(V_P_SS *arguments)
    : Controller(arguments)
{ 
    simple_gui_ = new gui::SimpleGuiCV();
}

GuiController::~GuiController()
{ 
    delete simple_gui_;
}

void GuiController::run()
{
    // image
    simple_gui_->create_window(IMAGE_WINDOW_NAME_);
    simple_gui_->show(*image_, IMAGE_WINDOW_NAME_);
    // histogram
    simple_gui_->create_window(HISTOGRAM_WINDOW_NAME_);
    img::Image *himg = histogram_.saveAsImage();
    simple_gui_->show(*himg, HISTOGRAM_WINDOW_NAME_);
    delete himg;
    // run operations
    Controller::run();
    simple_gui_->wait();
    // update windows
    simple_gui_->show(*image_, IMAGE_WINDOW_NAME_);
    himg = histogram_.saveAsImage();
    simple_gui_->show(*himg, HISTOGRAM_WINDOW_NAME_);
    delete himg;
    simple_gui_->wait();
    // destroy windows
    simple_gui_->close_window(IMAGE_WINDOW_NAME_);
    simple_gui_->close_window(HISTOGRAM_WINDOW_NAME_);
}


} // namespace imgprocapp
