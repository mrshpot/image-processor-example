#pragma once

#include <string>
#include <stdint.h>


class Image
{
public:
    typedef uint8_t byte_t;

private:
    int m_width, m_height;
    byte_t *m_data;

public:
    Image(int width, int height);
    Image(const std::string &from_file);
    ~Image();

    byte_t* data();
    int width() const;
    int height() const;
    int components() const;
    void write_to_file(const std::string &filename);

    // disable copying
    Image(const Image &) = delete;
    Image& operator=(const Image &) = delete;
};
