/**
 *      Purpose:
 *          This class is an extension of Controller. It adds gui functionality to its parent.
 *
 *      Created:    13th Oct 2016
 *      Author(s):  Jakub Precht
 */

#ifndef GUI_CONTROLLER_HPP
#define GUI_CONTROLLER_HPP

#include "img/Image.hpp"
#include "gui/SimpleGui.hpp"
#include "Controller.hpp"


namespace imgprocapp
{

class GuiController : public Controller
{
  public:
    /* remembers gui and passes the rest to parent constructor */
    GuiController(V_P_SS *arguments);
    ~GuiController();
    
    /* creates and manages gui, calls parent merhod run to perform operations on image 
     * due to passed arguments */
    void run();

  private:
    gui::SimpleGui *simple_gui_;
};

} // namespace imgprocapp

#endif // GUI_CONTROLLER_HPP


