#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>

#include "ImageProcessor.hpp"
#include "ImageProcessorException.hpp"
#include "Image.hpp"

using std::cout;
using std::endl;

using std::string;
using std::vector;


int string_to_int(const string &s)
{
    std::istringstream iss(s);
    int value;
    iss >> value;
    if (iss.fail())
    {
        std::ostringstream error_stream;
        error_stream << "Invalid number: '" << s << "'";
        throw ImageProcessorException(error_stream.str());
    }
    return value;
}

void ImageProcessor::print_command_usage()
{
    cout << "gen-test-image <out-filename>" << endl;
    cout << "copy <in-filename> <out-filename>" << endl;
}

void ImageProcessor::execute_command(const string &command, const vector<string> &args)
{
    if (command == "gen-test-image")
    {
        cmd_gen_test_image(args);
    }
    else if (command == "copy")
    {
        cmd_copy(args);
    }
    else
    {
        std::ostringstream error_stream;
        error_stream << "Unrecognized command: " << command;
        throw ImageProcessorException(error_stream.str());
    }
}

void ImageProcessor::cmd_gen_test_image(const vector<string> &args)
{
    if (args.size() != 1)
        throw ImageProcessorException("gen-test-image expects one argument");

    string out_filename = args[0];

    int width = 1024;
    int height = 768;
    Image image(width, height);
    assert(image.components() == 4);
    Image::byte_t *data = image.data();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int size = 512 / 8;
            bool black = (x / size + y / size) % 2 == 0;
            data[0] = black ? 255 : 0;
            data[1] = black ? 255 : 0;
            data[2] = black ? 255 : 0;
            data[3] = 255;
            data += 4;
        }
    }
    image.put_pixel(10, 10, 255, 0, 0);
    image.put_pixel(11, 10, 255, 0, 0);
    image.put_pixel(10, 11, 255, 0, 0);
    image.put_pixel(11, 11, 255, 0, 0);
    
    image.put_pixel(100, 10, 0, 255, 0);
    image.put_pixel(101, 10, 0, 255, 0);
    image.put_pixel(100, 11, 0, 255, 0);
    image.put_pixel(101, 11, 0, 255, 0);
    
    image.put_pixel(20, 150, 0, 0, 255);
    image.put_pixel(21, 150, 0, 0, 255);
    image.put_pixel(20, 151, 0, 0, 255);
    image.put_pixel(21, 151, 0, 0, 255);

    image.write_to_file(out_filename);
}

void ImageProcessor::cmd_copy(const vector<string> &args)
{
    if (args.size() != 2)
        throw ImageProcessorException("copy expects two arguments");

    string in_filename = args[0];
    string out_filename = args[1];

    Image image(in_filename);
    image.write_to_file(out_filename);
}
