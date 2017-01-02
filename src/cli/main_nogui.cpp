#include "cli/Controller.hpp"

#include <iostream>

int main(int argc, char **argv)
{
    try {
        imgproc::cli::Controller ctr(argc, argv);
        ctr.run();
    }
    catch(const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
        return 1;
    }

    return 0;
}

