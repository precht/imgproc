/**
 *      Purpose:
 *          This file contains only main function. The function choose Image and SimpleGui
 *          implementation by creating these objects and then calls Controller to process.
 *
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "Controller.hpp"
#include "GuiController.hpp"

int main(int argc, char **argv)
{
    imgprocapp::GuiController ctr(imgprocapp::Controller::read_arguments(argc, argv));
    ctr.run();

    return 0;
}

