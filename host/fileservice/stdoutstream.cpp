#include <iostream>

#include "stdoutstream.hpp"

namespace FileService
{
    StdOutStream::StdOutStream(const std::string& title) :
        title(title)
    {
        *this << '+'  << std::string(78, '-')                           << "+" << std::endl;
        *this << "| " << title << std::string(77 - title.length(), ' ') << "|" << std::endl;
        *this << '+'  << std::string(78, '-')                           << "+" << std::endl;
    }

    StdOutStream::~StdOutStream()
    {
        flush();
    }

    std::ostream& StdOutStream::flush()
    {
        *this << std::string(80, '~') << std::endl;

        std::cout << this->str() << std::endl;

        // clear the buffer
        this->str(std::string());

        return *this;
    }
}
