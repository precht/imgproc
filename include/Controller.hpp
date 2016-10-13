/**
 *      Purpose:
 *          The main purpose for Controller class is to call proper operations on image due to
 *          passed arguments.
 *
 *      Created:    12th Oct 2016
 *      Author:     Jakub Precht
 */

#include "image/Image.hpp"

#include <map>
#include <memory>
#include <iostream>


namespace imgprocapp
{

typedef std::unique_ptr<std::map<std::string, int>> UPTR_M_SI;

class Controller
{
  public:

    /* reads arguments and returns map with command-value entries */
    static UPTR_M_SI read_arguments(int argc, char **argv);

    /* constructs Controller using passed Image implementation and map from function
     * Controller::read_arguments */
    Controller(image::SPTR_IMG image, UPTR_M_SI arguments);

    virtual ~Controller();
    virtual void run();

  private:
    UPTR_M_SI arguments_;
    image::SPTR_IMG image_;
};

} // namespace imgprocapp

