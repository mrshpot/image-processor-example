#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

#include "ImageProcessor.hpp"

using std::cout;
using std::cerr;
using std::endl;


void print_usage(const std::string &argv0)
{
    cout << "Usage: " << argv0 << " <command> <options>" << endl;
    cout << "Commands:" << endl;
    ImageProcessor::print_command_usage();
}

int main(int argc, char *argv[])
{
    // Usage: program <command> <command-args>
    // Expect command as first argument
    std::string argv0 = argv[0];
    if (argc < 2)
    {
        cerr << "Error: Expected at least one argument: command" << endl;
        print_usage(argv0);
        return 1;
    }
    std::string command = argv[1];

    // Print help message if requested
    if (command == "help" || command == "--help")
    {
        print_usage(argv0);
        return 0;
    }

    // Retrieve command arguments
    // skip argv[0]: executable and argv[1]: command
    const int command_args_offset = 2; 
    int num_command_args = argc - command_args_offset;
    std::vector<std::string> command_args(num_command_args);
    for (int i = 0; i < num_command_args; ++i)
    {
        command_args[i] = argv[i + command_args_offset];
    }
    
    try
    {
		ImageProcessor processor;
        processor.execute_command(command, command_args);
    }
    catch(const std::exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
