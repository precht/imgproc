/**
 *      Purpose:
 *          This file contains only main function. The function choose Image and SimpleGui
 *          implementation by creating these objects and then calls Controller to process.
 *
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "image/Image.hpp"
#include "image/ImageCV.hpp"
#include "gui/SimpleGui.hpp"
#include "gui/SimpleGuiCV.hpp"
#include "Controller.hpp"
#include "GuiController.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using namespace imgprocapp;
using namespace imgprocapp::image;
using namespace imgprocapp::gui;
using namespace std;

typedef unique_ptr<map<string, int>> UPTR_M_SI;

int main(int argc, char **argv)
{
    try
    {
        GuiController ctr(Controller::read_arguments(argc, argv));
        ctr.run();
    } 
    // TODO porp except
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

