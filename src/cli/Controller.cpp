/**
 *      Created:    13th Oct 2016
 *      Author:     Jakub Precht
 */

#include "core/core.hpp"
#include "cli/Controller.hpp"
#include "opencv/OpenCVImageHelper.hpp"

#include <regex>
#include <cstring>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <memory>

namespace imgproc
{
namespace cli
{

using namespace core;
using namespace opencv;
using std::cout;
using std::cerr;
using std::endl;

// TODO: change all

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
                    cout << HELP_CONTENT << endl;
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
        cerr << "No input name" << endl;
        std::exit(EXIT_FAILURE);
    }
    if(multiple_input_names)
    {
        cerr << "Multiple input names" << endl;
        std::exit(EXIT_FAILURE);
    }
    if(multiple_output_names)
    {
        cerr << "Multiple output names" << endl;
        std::exit(EXIT_FAILURE);
    }
    if(v->at(1).second.compare("") == 0) v->at(1).second = DEFAULT_OUTPUT_NAME;

    return v;
}

Controller::Controller(V_P_SS *arguments)
    : arguments_(arguments)
    , helper_(std::make_shared<OpenCVImageHelper>())
    , image_(helper_, arguments_->at(0).second, arguments_->at(1).second)
{
    try
    {
        if(!image_.load()) throw "failed to load image, probably wrong name";
        histogram_.create(image_);
    }
    catch (const char *e)
    {
        cerr << e << endl;
        std::exit(EXIT_FAILURE);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        std::exit(EXIT_FAILURE);
    }
}

Controller::~Controller()
{
//    delete arguments_;
}

//// TODO this method it too long
void Controller::run()
{
//    cout << "Input image:" << endl << img::utils::CharacteristicUtils::all(histogram_) << endl;
    bool modified_image = false;
    try
    {
        for(auto it = arguments_->begin() + 2; it != arguments_->end(); ++it)
        {
            
            // Negative
            if(it->first.compare(NEGATIVE) == 0)
            {
                if(it->second.compare("") != 0) throw "Negative option shouldn't have any value";
                BasicUtils::negate(image_);
                modified_image = true;
            }
            // Brightness
            else if(it->first.compare(BRIGHTNESS) == 0)
            {
                std::regex rgx("^-?\\d+$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong brightness value";
                int shift = std::stoi(it->second);
                if(std::abs(shift) >= Image::CHANNEL_RANGE) throw "Wrong brightness value";
                BasicUtils::brightness(image_, shift);
                modified_image = true;
            }
            // Contrast
            else if(it->first.compare(CONTRAST) == 0)
            {
                std::regex rgx("^-?\\d+\\.?\\d*$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong contrast value";
                double slope = std::stod(it->second);
                BasicUtils::contrast(image_, slope);
                modified_image = true;
            }
            // Fliping
            else if(it->first.compare(HORIZONTAL_FLIP) == 0)
            {
                if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
                GeometricUtils::horizontalFlip(image_);
                modified_image = true;
            }
            else if(it->first.compare(VERTICAL_FLIP) == 0)
            {
                if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
                GeometricUtils::verticalFlip(image_);
                modified_image = true;
            }
            else if(it->first.compare(DIAGONAL_FLIP) == 0)
            {
                if(it->second.compare("") != 0) throw "Flip option shouldn't have any value";
                GeometricUtils::diagonalFlip(image_);
                modified_image = true;
            }
            // Scaling
            else if(it->first.compare(SHRINK) == 0)
            {
                std::regex rgx("^[1-9]\\d*\\.?\\d*$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong shrinking value";
                double times = std::stod(it->second);
                GeometricUtils::scale(image_, 1 / times);
                modified_image = true;
            }
            else if(it->first.compare(ENLARGE) == 0)
            {
                std::regex rgx("^[1-9]\\d*\\.?\\d*$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong enlarging value";
                double times = std::stod(it->second);
                GeometricUtils::scale(image_, times);
                modified_image = true;
            }
            // Filters
            // TODO add option to set radius
            else if(it->first.compare(GEOMETRIC_MEAN_FILTER) == 0)
            {
                if(it->second.compare("") != 0) throw "Geometric filter shouldn't have any value";
                NoiseRemovalUtils::geometricMeanFilter(image_);
                modified_image = true;
            }
            else if(it->first.compare(ALPHA_TRIMMED_MEAN_FILTER) == 0)
            {
                std::regex rgx("^\\d+$");
                if(!std::regex_match(it->second, rgx)) throw "Wrong alpha value";
                int alpha = std::stoi(it->second);
                NoiseRemovalUtils::alphaTrimmedMeanFilter(image_, alpha);
                modified_image = true;
            }
            // Errors
            // TODO elegant messages on screen
            else if(it->first.compare(MAXIMUM_DIFFERENCE) == 0)
            {
                Image orginal(helper_, it->second);
                cout << ErrorMeasureUtils::maximumDifference(orginal, image_) << endl;
            }
            else if(it->first.compare(MEAN_SQUARE_ERROR) == 0)
            {
                Image orginal(helper_, it->second);
                cout << ErrorMeasureUtils::meanSquareError(orginal, image_) << endl;
            }
            else if(it->first.compare(PEAK_MEAN_SQUARE_ERROR) == 0)
            {
                Image orginal(helper_, it->second);
                cout << ErrorMeasureUtils::peakMeanSquareError(orginal, image_) << endl;
            }
            else if(it->first.compare(SIGNAL_NOISE_RATIO) == 0)
            {
                Image orginal(helper_, it->second);
                cout << ErrorMeasureUtils::signalToNoiseRatio(orginal, image_) << endl;
            }
            else if(it->first.compare(PEAK_SIGNAL_NOISE_RATIO) == 0)
            {
                Image orginal(helper_, it->second);
                cout << ErrorMeasureUtils::peakSignalToNoiseRatio(orginal, image_) << endl;
            }
            // Quality imporvement
            else if(it->first.compare(HUNIFORM) == 0)
            {
                int gmin, gmax;
                std::regex rgx("^([0-9]\\d*),([0-9]\\d*)$");
                std::smatch match;
                if(std::regex_search(it->second, match, rgx) && match.size() == 3) {
                    gmin = std::stoi(match[1]);
                    gmax = std::stoi(match[2]);
                    QualityImprovementUtils::uniformFinalProbabilityDensity(image_, histogram_, gmin, gmax);
                }
                else QualityImprovementUtils::uniformFinalProbabilityDensity(image_, histogram_);
                modified_image = true;
            }
            else if(it->first.compare(SLINEID) == 0)
            {
                if(it->second != "")
                {
                    std::regex rgx("^[1234]$");
                    if(!std::regex_match(it->second, rgx)) throw "Wrong line identification value";
                    LinearFiltrationUtils::lineIdentification(image_, std::stoi(it->second));
                }
                else LinearFiltrationUtils::lineIdentification(image_);
                modified_image = true;
            }
            else if(it->first.compare(UOLIS) == 0)
            {
                NonLinearFiltrationUtils::uolis(image_);
                modified_image = true;
            }
            // characteristics
            else if(it->first.compare(CALL) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::all(histogram_) << endl;
            }
            else if(it->first.compare(CMEAN) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::mean(histogram_) << endl;
            }
            else if(it->first.compare(CVARIANCE) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::variance(histogram_) << endl;
            }
            else if(it->first.compare(CSTDEV) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::standardDeviation(histogram_) << endl;
            }
            else if(it->first.compare(CASYCO) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::asymmetryCoefficient(histogram_) << endl;
            }
            else if(it->first.compare(CFLATCO) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::flatteningCoefficient(histogram_) << endl;
            }
            else if(it->first.compare(CVARCOI) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::variationCoefficient1(histogram_) << endl;
            }
            else if(it->first.compare(CVARCOII) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::variationCoefficient2(histogram_) << endl;
            }
            else if(it->first.compare(CENTROPY) == 0)
            {
                histogram_.create(image_);
                cout << CharacteristicUtils::informationSourceEntropy(histogram_) << endl;
            }
            else if(it->first.compare(EROSION) == 0)
            {
                MorphologicalUtils::erosion(image_);
                modified_image = true;
            }
            else if(it->first.compare(DILATION) == 0)
            {
                MorphologicalUtils::dilation(image_);
                modified_image = true;
            }
            else if(it->first.compare(OPENING) == 0)
            {
                MorphologicalUtils::opening(image_);
                modified_image = true;
            }
            else if(it->first.compare(CLOSING) == 0)
            {
                MorphologicalUtils::closing(image_);
                modified_image = true;
            }
			else if (it->first.compare(HMT) == 0)
			{
				MorphologicalUtils::hmt(image_);
				modified_image = true;
			}
            else if(it->first.compare(THICKENING) == 0)
            {
                MorphologicalUtils::thickening(image_);
                modified_image = true;
            }
			else if (it->first.compare(DELTARG) == 0)
			{
                int seed_x, seed_y, lower_delta, higher_delta;
                std::regex rgx("^([0-9]\\d*),([0-9]\\d*),([0-9]\\d*),([0-9]\\d*)$");
				std::smatch match;
                if (std::regex_search(it->second, match, rgx) && match.size() == 5) {
                    seed_x =  std::stoi(match[1]);
                    seed_y = std::stoi(match[2]);
                    lower_delta = std::stoi(match[3]);
                    higher_delta = std::stoi(match[4]);
                    SegmentationUtils::deltaRegionGrowing(image_, seed_x, seed_y, lower_delta, higher_delta);
				}
                else std::cout << "Wrong delta region growing arguments" << std::endl;
				modified_image = true;
			}
            else if (it->first.compare(RANGERG) == 0)
            {
                int seed_x, seed_y, lower_delta, higher_delta;
                std::regex rgx("^([0-9]\\d*),([0-9]\\d*),([0-9]\\d*),([0-9]\\d*)$");
                std::smatch match;
                if (std::regex_search(it->second, match, rgx) && match.size() == 5) {
                    seed_x =  std::stoi(match[1]);
                    seed_y = std::stoi(match[2]);
                    lower_delta = std::stoi(match[3]);
                    higher_delta = std::stoi(match[4]);
                    SegmentationUtils::rangeRegionGrowing(image_, seed_x, seed_y, lower_delta, higher_delta);
                }
                else std::cout << "Wrong range region growing arguments" << std::endl;
                modified_image = true;
            }
            else if(it->first.compare(HISTOGRAM) == 0)
            {
                histogram_.create(image_);
                std::string name = "a_histogram.bmp";
                if(it->second != "")
                    name = it->second;
                histogram_.toImage()->save(name);
            }
            else if (it->first.compare(FFT) == 0)
            {
                Image output1(image_);
                Image output2(image_);
                auto matrix = FrequencyDomainUtils::fastFourierTransform(image_);
                FrequencyDomainUtils::complexMatrixToImages(*(matrix.get()), output1, output2, CT_PHASE_MAGNITUDE);
                FrequencyDomainUtils::inverseFastFourierTransform(image_, *(matrix.get()));

                output1.save("a_1.bmp");
                output2.save("a_2.bmp");
                modified_image = true;
            }
            // Default, wrong input args
            else throw "Unknown option";
        }
        if(modified_image) image_.save();
    }
    catch (const char *e)
    {
        cerr << e << endl;
        std::exit(EXIT_FAILURE);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        std::exit(EXIT_FAILURE);
    }
    histogram_.create(image_);
//    cout << "Output image:" << endl << img::utils::CharacteristicUtils::all(histogram_) << endl;
}

} // cli
} // imgprocapp


