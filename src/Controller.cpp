/**
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#include "Controller.hpp"
#include "img/ImageCV.hpp"
#include "img/utils/utils.hpp"

#include <regex>
#include <cstring>
#include <iostream>
#include <cassert>



namespace imgprocapp
{

V_P_SS *Controller::read_arguments(int argc, char **argv)
{
    V_P_SS *v = new V_P_SS();
    v->push_back(P_SS(INPUT_NAME, ""));
    v->push_back(P_SS(INPUT_NAME, ""));
    // regex that will find options arguments
    std::regex rgx("^--?([a-zA-z]+)=?(.*)$");
    for(unsigned i = 1; i < argc; ++i) {
        std::cmatch match;
        if(std::regex_search(argv[i], match, rgx))
        {
            if(match.size() == 3) // there is command and value
            {
                if(match[1] == INPUT_NAME) 
                {
                    if( v->at(0).second.compare("")) throw "Multiple input names";
                    v->at(0).second = std::string(match[2]);
                }
                else if(match[1] == OUTPUT_NAME) 
                {
                    if( v->at(1).second.compare("")) throw "Multiple output names";
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
    // TODO throw porper exception
    if(v->at(0).second.compare("") == 0) throw "Controller: No input name"; 
    if(v->at(1).second.compare("") == 0) v->at(1).second = DEFAULT_OUTPUT_NAME;

    return v;
}

Controller::Controller(V_P_SS *arguments)
    : arguments_(arguments)
{ 
    image_ = new img::ImageCV(arguments_->at(0).second, arguments_->at(1).second);
}

Controller::~Controller()
{ 
    delete image_;
    delete arguments_;
}

// TODO this method it too long
void Controller::run()
{ 
    for(auto it = arguments_->begin() + 2; it != arguments_->end(); ++it)
    {
        // Negative
        if(it->first.compare(NEGATIVE) == 0) 
        {
            if(it->second.compare("") != 0) throw "Negative option shouldn't have any value";
            img::utils::BasicUtils::negate(image_);
        }
        // Brightness
        else if(it->first.compare(BRIGHTNESS) == 0) 
        {
            std::regex rgx("^-?\\d+$");
            if(!std::regex_match(it->second, rgx)) throw "Wrong brightness value";
            int shift = std::stoi(it->second);
            img::utils::BasicUtils::change_brightness(image_, shift);
        }
        // Contrast
        else if(it->first.compare(CONTRAST) == 0) 
        {
            std::regex rgx("^-?\\d+\\.?\\d*$");
            if(!std::regex_match(it->second, rgx)) throw "Wrong contrast value";
            double slope = std::stod(it->second);
            img::utils::BasicUtils::change_contrast(image_, slope);
        }
        // Fliping
        else if(it->first.compare(HORIZONTAL_FLIP) == 0)
        {
            if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
            img::utils::GeometricUtils::flip_horizontally(image_);
        }
        else if(it->first.compare(VERTICAL_FLIP) == 0)
        {
            if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
            img::utils::GeometricUtils::flip_vertically(image_);
        }
        else if(it->first.compare(DIAGONAL_FLIP) == 0)
        {
            if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
            img::utils::GeometricUtils::flip_diagonally(image_);
        }
        // Scaling
        else if(it->first.compare(SHRINK) == 0)
        {
            std::regex rgx("^[1-9]\\d*\\.?\\d*$");
            if(!std::regex_match(it->second, rgx)) throw "Wrong shrinking value";
            double times = std::stod(it->second);
            img::utils::GeometricUtils::scale(image_, 1 / times);
        }
        else if(it->first.compare(ENLARGE) == 0)
        {
            std::regex rgx("^[1-9]\\d*\\.?\\d*$");
            if(!std::regex_match(it->second, rgx)) throw "Wrong enlarging value";
            double times = std::stod(it->second);
            img::utils::GeometricUtils::scale(image_, times);
        }
        // Filters
        // TODO add option to set radius
        else if(it->first.compare(GEOMETRIC_MEAN_FILTER) == 0)
        {
            if(it->second.compare("") != 0) throw "Geometric filter shouldn't have any value";
            img::utils::NoiseRemovalUtils::geometric_mean_filter(image_);
        }
        else if(it->first.compare(ALPHA_TRIMMED_MEAN_FILTER) == 0)
        {
            std::regex rgx("^\\d*[02468]$");
            if(!std::regex_match(it->second, rgx)) throw "Wrong alpha value";
            int alpha = std::stoi(it->second);
            img::utils::NoiseRemovalUtils::alpha_trimmed_mean_filter(image_, alpha);
        }
        // Default, wrong input args
        else throw "Unknown option";
    }
    image_->save_image();
}

} // namespace imgprocapp


