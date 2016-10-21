/**
 *      Purpose:
 *          This is an abstract class prividing methods to create a simple window and display
 *          in it image. It's behaviour shouldn't depend on derived class implementation.
 *
 *      Created:    12th Oct 2016
 *      Author(s):     Jakub Precht
 */

#ifndef SIMPLE_GUI_HPP
#define SIMPLE_GUI_HPP

#include "img/Image.hpp"

namespace imgprocapp
{
namespace gui
{

class SimpleGui
{
  public:
    virtual ~SimpleGui();
    virtual void create_window() = 0;
    virtual void show(img::Image &image) = 0;
    virtual void close_window() = 0;

    /* wait for user action */
    virtual void wait() = 0;
};

} // namespace gui
} // namespace imgprocapp

#endif // SIMPLE_GUI_HPP
