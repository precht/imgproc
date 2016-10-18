/**
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#include "Controller.hpp"
#include "image/ImageCV.hpp"
#include "image/utils/BasicUtils.hpp"

#include <regex>
#include <cstring>
#include <iostream>
#include <cassert>



namespace imgprocapp
{

V_P_SS *Controller::read_arguments(int argc, char **argv)
{
    std::vector<std::pair<std::string, std::string>> *v = 
            new std::vector<std::pair<std::string, std::string>>();
    v->push_back(std::pair<std::string, std::string>(INPUT_NAME, ""));
    v->push_back(std::pair<std::string, std::string>(INPUT_NAME, ""));
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
                    v->push_back(std::pair<std::string, std::string>(std::string(match[1]), 
                            std::string(match[2])));
                }
            }
            else if(match.size() == 2) // there is only command
                v->push_back(std::pair<std::string, std::string>(std::string(match[1]), ""));
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
    image_ = new image::ImageCV(arguments_->at(0).second, arguments_->at(1).second);
}

Controller::~Controller()
{ 
    delete image_;
    delete arguments_;
}

void Controller::run()
{ 
    for(auto it = arguments_->begin() + 2; it != arguments_->end(); ++it)
    {
        // Negative
        if(it->first.compare(NEGATIVE) == 0) image::utils::BasicUtils::negate(image_);
        // Brightness
        else if(it->first.compare(BRIGHTNESS) == 0) 
        {
            int shift;
            // TODO porp except
            try 
            {
                shift = std::stoi(it->second);
            } 
            catch (const std::exception& e) 
            {
                throw "Failed to convert brightness value to int, probably incorrect input";
            }
            image::utils::BasicUtils::change_brightness(image_, shift);
        }
        // Contrast
        else if(it->first.compare(CONTRAST) == 0) 
        {
            double slope;
            // TODO porp except
            try 
            {
                slope = std::stod(it->second);
            } 
            catch (const std::exception& e) 
            {
                throw "Failed to convert contrast value to double, probably incorrect input";
            }
            image::utils::BasicUtils::change_contrast(image_, slope);
        }
        // Default, wrong input args
        else throw "Unknown option";
    }
    image_->save_image();
}

} // namespace imgprocapp


