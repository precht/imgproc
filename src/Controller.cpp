/**
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "Controller.hpp"
#include "image/Image.hpp"

namespace imgprocapp
{

UPTR_M_SI Controller::read_arguments(int argc, char **argv)
{
    UPTR_M_SI uptr = UPTR_M_SI(new std::map<std::string, int>);
    return uptr;
}

Controller::Controller(image::SPTR_IMG image, UPTR_M_SI arguments)
    : image_(std::move(image))
    , arguments_(std::move(arguments))
{ }

Controller::~Controller()
{ }

void Controller::run()
{ }

} // namespace imgprocapp


