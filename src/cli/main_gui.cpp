/**
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "cli/Controller.hpp"
#include "cli/GuiController.hpp"

int main(int argc, char **argv)
{
    auto args = imgproc::cli::Controller::read_arguments(argc, argv);
    imgproc::cli::GuiController ctr(args);
    ctr.run();
    delete args;
    return 0;
}

