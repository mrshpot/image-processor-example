#pragma once

#include <string>
#include <stdint.h>


class Image
{
public:
    typedef uint8_t byte_t;
    typedef uint32_t rgb_t;

    // such an enum is a way to set a constant
    enum {
        NUM_COMPONENTS = 4 // always RGBA for now
    };
    
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

public:
    // inline functions
    void put_pixel(int x, int y, byte_t r, byte_t g, byte_t b, byte_t a=255)
    {
        byte_t *pixel = &(m_data[(y * m_width + x) * NUM_COMPONENTS]);
        pixel[0] = r;
        pixel[1] = g;
        pixel[2] = b;
        pixel[3] = a;
    }
    
    void get_pixel(int x, int y, byte_t *r, byte_t *g, byte_t *b, byte_t *a)
    {
        byte_t *pixel = &(m_data[(y * m_width + x) * NUM_COMPONENTS]);
        *r = pixel[0];
        *g = pixel[1];
        *b = pixel[2];
        *a = pixel[3];
    }

    void put_pixel(int x, int y, rgb_t rgb, byte_t a=255)
    {
        byte_t r = (rgb & 0x0000FF);
        byte_t g = (rgb & 0x00FF00) >> 8;
        byte_t b = (rgb & 0xFF0000) >> 16;
        put_pixel(x, y, r, g, b, a);
    }
};
