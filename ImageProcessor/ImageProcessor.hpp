#pragma once

#include <vector>
#include <string>


class ImageProcessor
{
public:
    static void print_command_usage();

    void execute_command(const std::string &command, const std::vector<std::string> &args);

    void cmd_gen_test_image(const std::vector<std::string> &args);
    void cmd_copy(const std::vector<std::string> &args);
};
