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
    
    int width = 256;
    int height = 256;
    Image image(width, height);
    assert(image.components() == 4);
    Image::byte_t *data = image.data();
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int offset = ((i * height) + j) * 4;
            data[offset + 0] = (i % 40 == 0) ? 255 : 0;
            data[offset + 1] = (j % 50 == 0) ? 255 : 0;
            data[offset + 2] = (i * j % 60 == 0) ? 255 : 0;
            data[offset + 3] = 255;
        }
    }

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
