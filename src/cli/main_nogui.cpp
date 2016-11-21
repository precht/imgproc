/**
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "cli/Controller.hpp"

int main(int argc, char **argv)
{
    imgproc::cli::Controller ctr(imgproc::cli::Controller::read_arguments(argc, argv));
    ctr.run();

    return 0;
}

