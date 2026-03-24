#include <iostream>

#include "stdoutpseudofile.hpp"

StdOutPseudoFile::StdOutPseudoFile(const std::string& title) :
    title(title)
{
    *this << '+'  << std::string(78, '-')                           << "+" << std::endl;
    *this << "| " << title << std::string(77 - title.length(), ' ') << "|" << std::endl;
    *this << '+'  << std::string(78, '-')                           << "+" << std::endl;
}

StdOutPseudoFile::~StdOutPseudoFile()
{
    flush();
}

std::ostream& StdOutPseudoFile::flush()
{
    *this << std::string(80, '~') << std::endl;

    std::cout << this->str() << std::endl;

    // clear the buffer
    this->str(std::string());

    return *this;
}
