#ifndef STDOUTPSEUDOFILE_H
#define STDOUTPSEUDOFILE_H

#include <sstream>

class StdOutPseudoFile : public std::ostringstream
{
    private:
        std::string title;

    public:
        StdOutPseudoFile(const std::string& title);
        ~StdOutPseudoFile();

        std::ostream& flush();
};

#endif // STDOUTPSEUDOFILE_H
