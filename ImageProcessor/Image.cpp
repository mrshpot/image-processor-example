#include <string>
#include <sstream>
#include <assert.h>

// third-party libraries for reading & writing images
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include "Image.hpp"
#include "ImageProcessorException.hpp"


static const int NUM_COMPONENTS = 4; // always RGBA for now

Image::Image(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_data(new byte_t[width * height * NUM_COMPONENTS])
{
}

Image::Image(const std::string &from_file)
{
    static_assert(sizeof(stbi_uc) == sizeof(byte_t), "Byte size mismatch with stb_image");
    int req_comp = NUM_COMPONENTS;
    int w, h, comp;
    stbi_uc *image_data = stbi_load(from_file.c_str(), &w, &h, &comp, req_comp);
    if (image_data == NULL)
    {
        std::ostringstream error_stream;
        error_stream << "Could not load image '" << from_file << "': " << stbi_failure_reason();
        throw ImageProcessorException(error_stream.str());
    }
    if (comp != req_comp)
    {
        stbi_image_free(image_data);
        std::ostringstream error_stream;
        error_stream << "Expected " << req_comp << " components, got " << comp;
        throw ImageProcessorException(error_stream.str());
    }
    
    // copy to a new[]-allocated buffer for implementation simplicity
    size_t data_size = w * h * comp;
    byte_t *data = new byte_t[data_size];
    memcpy(data, image_data, data_size);
    stbi_image_free(image_data);

    m_width = w;
    m_height = h;
    m_data = data;
}

Image::~Image()
{
    delete[] m_data;
}

Image::byte_t* Image::data()
{
    return m_data;
}

int Image::width() const
{
    return m_width;
}

int Image::height() const
{
    return m_height;
}

int Image::components() const
{
    return NUM_COMPONENTS;
}

void Image::write_to_file(const std::string &filename)
{
    int w = width();
    int h = height();
    int comp = components();
    int stride = w * comp;
    int rc = stbi_write_png(filename.c_str(), w, h, comp, data(), stride);
    if (rc == 0) // returns 0 on failure
    {
        std::ostringstream error_stream;
        error_stream << "Could not write '" << filename << "'";
        throw ImageProcessorException(error_stream.str());
    }
}
