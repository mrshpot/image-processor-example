#pragma once

#include <exception>
#include <string>


class ImageProcessorException : public std::exception
{
    std::string m_message;
    
public:
    ImageProcessorException(const std::string &message)
        : m_message(message)
    {
    }

    virtual const char *what() const throw()
    {
        return m_message.c_str();
    }
};
