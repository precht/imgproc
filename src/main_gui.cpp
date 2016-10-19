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

#include <exception>
#include <iostream>

using namespace imgprocapp;
using namespace std;

int main(int argc, char **argv)
{
    try
    {
        GuiController ctr(Controller::read_arguments(argc, argv));
        ctr.run();
    } 
    catch (char const *e)
    {
        cerr << e << endl;
    }
    catch (const exception& e) 
    {
        cerr << e.what() << endl;
    }

    return 0;
}

