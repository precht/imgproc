/**
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "cli/Controller.hpp"
#include "cli/GuiController.hpp"

int main(int argc, char **argv)
{
    imgproc::cli::GuiController ctr(imgproc::cli::Controller::read_arguments(argc, argv));
    ctr.run();
    return 0;
}

