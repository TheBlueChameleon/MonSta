#include <iostream>

#include "stdoutpseudofile.hpp"

StdOutPseudoFile::StdOutPseudoFile(const std::string& title) :
    title(title)
{}

StdOutPseudoFile::~StdOutPseudoFile()
{
    flush();
}

std::ostream& StdOutPseudoFile::flush()
{
    std::cout << '+'  << std::string(78, '-')                           << "+" << std::endl;
    std::cout << "| " << title << std::string(77 - title.length(), ' ') << "|" << std::endl;
    std::cout << '+'  << std::string(78, '-')                           << "+" << std::endl;

    std::cout << this->str() << std::endl;

    std::cout << std::string(80, '~') << std::endl;

    // clear the buffer
    this->str(std::string());

    return *this;
}
