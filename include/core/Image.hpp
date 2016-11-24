/**
 *      Created:    19th Nov 2016
 *      Author:     Jakub Precht
 *
 *
 *      Image with 3 channels is represented in following way:
 *
 *         |    0     |    1     |     columns (y axis) - its width depends on channels number
 *      ---+----------+----------+------>
 *       0 | c0 c1 c2 | c0 c1 c2 |
 *      ---+----------+----------+-
 *       1 | c0 c1 c2 | c0 c1 c2 |
 *      ---+----------+----------+-
 *         |
 *         V                    where: c0, c1, c2 are channels which together create one pixel
 *      rows (x axis)
 *
 *
 *      But in memory image is actually an one-dimensial array:
 *
 *      row     |              0              |              1              |
 *      --------+--------------+--------------+--------------+--------------+-
 *      column  |      0       |      1       |      0       |      1       |
 *      --------+----+----+----+----+----+----+----+----+----|----+----+----+-
 *      channel | c0 | c1 | c2 | c0 | c1 | c2 | c0 | c1 | c2 | c0 | c1 | c2 |
 *      --------+----+----+----+----+----+----+----+----+----|----+----+----+-
 *      memory  | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 |
 *
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <memory>
#include <ostream>
#include <string>

namespace imgproc
{
namespace core
{

struct ImageHelper;

class Image
{
public:
    const static int CHANNEL_RANGE = 256;
    const static int CHANNEL_MAX_VALUE= CHANNEL_RANGE - 1;

    Image();
    // new image data is filled with 0
    // neither of the constructors reads image from disc, you have to call load
    Image(std::shared_ptr<ImageHelper> helper, std::string input_name = "", std::string output_name_ = "");
    // If you want to save/load image you should implement ImageIO and pass in Image constructor
    Image(int rows, int columns, int channels, std::shared_ptr<ImageHelper> helper = nullptr,
          std::string input_name = "", std::string output_name = "");
    Image(const unsigned char *data, int rows, int columns, int channels,
          std::shared_ptr<ImageHelper> helper = nullptr, std::string input_name = "", std::string output_name = "");
    // Copyable
    Image(const Image& other);
    Image& operator=(const Image& other);
    // Movable
    Image(Image&& other);
    Image& operator=(Image&& other);
    virtual ~Image();

    int rows() const;
    int columns() const;
    int channels() const;
    int size() const;

    std::shared_ptr<ImageHelper> getHelper() const;
    void setHelper(std::shared_ptr<ImageHelper> helper);
    std::string getInputName() const;
    void setInputName(std::string input_name);
    std::string getOutputName() const;
    void setOutputName(std::string output_name);

    // parenthesis operator returns reference
    unsigned char& operator()(int index);
    unsigned char& operator()(int row, int column, int channel);
    // at function returns value (to get pixel values when Image is const)
    unsigned char at(int index) const;
    unsigned char at(int row, int column, int channel) const;

    bool load();
    bool save();
    // loading/saving with name will change image input/output name as well
    bool load(std::string name);
    bool save(std::string name);

    // resize will erase data
    void resize(int rows, int columns, int channels);
    // clear will earse data and set size to 0
    void clear();

    void swap(Image& other);

    // crop image specified number of pixels from each side
    void crop(int rows_from_start, int rows_from_end, int columns_from_start, int columns_from_end);

    // we cannnot overload operator<<, thus it will use virtual print function
    void print(std::ostream& where) const;
    friend std::ostream& operator<<(std::ostream& out, const Image& image);
    friend bool operator==(const Image& a, const Image& b);
    friend bool operator!=(const Image& a, const Image& b);

private:
    const static int MAX_CHANNELS = 4;

    int rows_;
    int columns_;
    int channels_;
    unsigned char *data_;
    std::shared_ptr<ImageHelper> helper_;
    std::string input_name_;
    std::string output_name_;
};

// Abstract struct providing methods depending external libraries
struct ImageHelper
{
    virtual bool load(Image& image) = 0;
    virtual bool save(Image& image) = 0;
    virtual ~ImageHelper() = default;
};

bool operator==(const Image& a, const Image& b);
bool operator!=(const Image& a, const Image& b);
std::ostream& operator<<(std::ostream& out, const Image& image);

} // namespace core
} // namespace imgproc


#endif // IMAGE_HPP_

