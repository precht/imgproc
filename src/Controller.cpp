/**
 *      Created:    13th Oct 2016
 *      Author(s):  Jakub Precht,
 *                  Olek Winogradow
 */

#include "Controller.hpp"
#include "img/ImageCV.hpp"
#include "img/utils/utils.hpp"

#include <regex>
#include <cstring>
#include <iostream>
#include <cassert>
#include <cstdlib>


namespace imgprocapp
{

V_P_SS *Controller::read_arguments(int argc, char **argv)
{
    V_P_SS *v = new V_P_SS();
    v->push_back(P_SS(INPUT_NAME, ""));
    v->push_back(P_SS(OUTPUT_NAME, ""));
    // regex that will find options arguments
    std::regex rgx("^--?([a-zA-z]+)=?(.*)$");
    bool multiple_input_names = false;
    bool multiple_output_names = false;
    for(int i = 1; i < argc; ++i) {
        std::cmatch match;
        if(std::regex_search(argv[i], match, rgx))
        {
            if(match.size() == 3) // there is command and value
            {
                if(match[1] == HELP)
                {
                    std::cout << HELP_CONTENT << std::endl;
                    std::exit(EXIT_SUCCESS);
                }
                if(match[1] == INPUT_NAME) 
                {
                    if(v->at(0).second.compare("")) multiple_input_names = true;
                    v->at(0).second = std::string(match[2]);
                }
                else if(match[1] == OUTPUT_NAME) 
                {
                    if(v->at(1).second.compare("")) multiple_output_names = true;
                    v->at(1).second = std::string(match[2]);
                }
                else 
                {
                    v->push_back(P_SS(std::string(match[1]), std::string(match[2])));
                }
            }
            else if(match.size() == 2) // there is only command
                v->push_back(P_SS(std::string(match[1]), ""));
            else assert(false); // if matched there should be one or two matches
        }
    }
    if(v->at(0).second.compare("") == 0)  
    {
        std::cerr << "No input name" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if(multiple_input_names)
    {
        std::cerr << "Multiple input names" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if(multiple_output_names)
    {
        std::cerr << "Multiple output names" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if(v->at(1).second.compare("") == 0) v->at(1).second = DEFAULT_OUTPUT_NAME;

    return v;
}

Controller::Controller(V_P_SS *arguments)
    : arguments_(arguments)
{ 
    try 
    {
        image_ = new img::ImageCV(arguments_->at(0).second, arguments_->at(1).second);
    }
    catch (const char *e)
    {
        std::cerr << e << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        exit (EXIT_FAILURE);
    }
}

Controller::~Controller()
{ 
    delete image_;
    delete arguments_;
}

// TODO this method it too long
void Controller::run()
{ 
    bool modified_image = false;
    try
    {
        for(auto it = arguments_->begin() + 2; it != arguments_->end(); ++it)
        {
            
            // Negative
            if(it->first.compare(NEGATIVE) == 0) 
            {
                if(it->second.compare("") != 0) throw "Negative option shouldn't have any value";
                img::utils::BasicUtils::negate(image_);
                modified_image = true;
            }
            // Brightness
            else if(it->first.compare(BRIGHTNESS) == 0) 
            {
                std::regex rgx("^-?\\d+$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong brightness value";
                int shift = std::stoi(it->second);
                if(std::abs(shift) >= img::COLORS_NUMBER) throw "Wrong brightness value";
                img::utils::BasicUtils::change_brightness(image_, shift);
                modified_image = true;
            }
            // Contrast
            else if(it->first.compare(CONTRAST) == 0) 
            {
                std::regex rgx("^-?\\d+\\.?\\d*$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong contrast value";
                double slope = std::stod(it->second);
                img::utils::BasicUtils::change_contrast(image_, slope);
                modified_image = true;
            }
            // Fliping
            else if(it->first.compare(HORIZONTAL_FLIP) == 0)
            {
                if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
                img::utils::GeometricUtils::flip_horizontally(image_);
                modified_image = true;
            }
            else if(it->first.compare(VERTICAL_FLIP) == 0)
            {
                if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
                img::utils::GeometricUtils::flip_vertically(image_);
                modified_image = true;
            }
            else if(it->first.compare(DIAGONAL_FLIP) == 0)
            {
                if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
                img::utils::GeometricUtils::flip_diagonally(image_);
                modified_image = true;
            }
            // Scaling
            else if(it->first.compare(SHRINK) == 0)
            {
                std::regex rgx("^[1-9]\\d*\\.?\\d*$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong shrinking value";
                double times = std::stod(it->second);
                img::utils::GeometricUtils::scale(image_, 1 / times);
                modified_image = true;
            }
            else if(it->first.compare(ENLARGE) == 0)
            {
                std::regex rgx("^[1-9]\\d*\\.?\\d*$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong enlarging value";
                double times = std::stod(it->second);
                img::utils::GeometricUtils::scale(image_, times);
                modified_image = true;
            }
            // Filters
            // TODO add option to set radius
            else if(it->first.compare(GEOMETRIC_MEAN_FILTER) == 0)
            {
                if(it->second.compare("") != 0) throw "Geometric filter shouldn't have any value";
                img::utils::NoiseRemovalUtils::geometric_mean_filter(image_);
                modified_image = true;
            }
            else if(it->first.compare(ALPHA_TRIMMED_MEAN_FILTER) == 0)
            {
                std::regex rgx("^\\d+$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong alpha value";
                int alpha = std::stoi(it->second);
                img::utils::NoiseRemovalUtils::alpha_trimmed_mean_filter(image_, alpha);
                modified_image = true;
            }
            // Errors
            // TODO elegant messages on screen
            else if(it->first.compare(MAXIMUM_DIFFERENCE) == 0)
            {
                img::ImageCV orginal(it->second, "");
                std::cout << img::utils::ErrorMeasureUtils::maximum_difference(&orginal, image_) 
                        << std::endl;
            }
            else if(it->first.compare(MEAN_SQUARE_ERROR) == 0)
            {
                img::ImageCV orginal(it->second, "");
                std::cout << img::utils::ErrorMeasureUtils::mean_square_error(&orginal, image_) 
                        << std::endl;
            }
            else if(it->first.compare(PEAK_MEAN_SQUARE_ERROR) == 0)
            {
                img::ImageCV orginal(it->second, "");
                std::cout << img::utils::ErrorMeasureUtils::peak_mean_square_error(&orginal, image_) 
                        << std::endl;
            }
            else if(it->first.compare(SIGNAL_NOISE_RATIO) == 0)
            {
                img::ImageCV orginal(it->second, "");
                std::cout << img::utils::ErrorMeasureUtils::signal_to_noise_ratio(&orginal, image_) 
                        << std::endl;
            }
            else if(it->first.compare(PEAK_SIGNAL_NOISE_RATIO) == 0)
            {
                img::ImageCV orginal(it->second, "");
                std::cout << img::utils::ErrorMeasureUtils::peak_signal_to_noise_ratio(&orginal, 
                        image_) << std::endl;
            }
            // Default, wrong input args
            else throw "Unknown option";
        }
        if(modified_image) image_->save_image();
    }
    catch (const char *e)
    {
        std::cerr << e << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

} // namespace imgprocapp


