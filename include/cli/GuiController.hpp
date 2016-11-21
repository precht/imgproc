/**
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#ifndef GUI_CONTROLLER_HPP_
#define GUI_CONTROLLER_HPP_

#include "core/Image.hpp"
#include "cli/Controller.hpp"
#include "opencv/OpenCVWindows.hpp"

namespace imgproc
{
namespace cli
{

class GuiController : public Controller
{
  public:
    /* remembers gui and passes the rest to parent constructor */
    GuiController(V_P_SS *arguments);
    virtual ~GuiController() = default;
    
    /* creates and manages gui, calls parent merhod run to perform operations on image 
     * due to passed arguments */
    void run();

  private:
    opencv::OpenCVWindows windows_;

    static const std::string IMAGE_WINDOW_NAME_;
    static const std::string HISTOGRAM_WINDOW_NAME_;
};

} // cli
} // imgproc

#endif // GUI_CONTROLLER_HPP_


