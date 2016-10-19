/**
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#include "GuiController.hpp"
#include "gui/SimpleGuiCV.hpp"

namespace imgprocapp
{

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
    simple_gui_->create_window();
    simple_gui_->show(*image_);
    // simple_gui_->wait();
    Controller::run();
    simple_gui_->wait();
    simple_gui_->show(*image_);
    simple_gui_->wait();
    simple_gui_->close_window();
}


} // namespace imgprocapp
