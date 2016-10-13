/**
 *      Purpose:
 *          This file contains only main function. The function choose Image and SimpleGui
 *          implementation by creating these objects and then calls Controller to process.
 *
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "Controller.hpp"
#include "image/Image.hpp"
#include "image/ImageCV.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <map>

using namespace imgprocapp;
using namespace imgprocapp::image;
using namespace std;

typedef unique_ptr<map<string, int>> UPTR_M_SI;

int main(int argc, char **argv)
{
    try
    {
        Controller ctr(make_shared<ImageCV>(""), Controller::read_arguments(argc, argv));
    }
    catch (std::exception& e)
    {
        cerr << "Exception caught: " << e.what() << endl;
    }
    return 0;
}

