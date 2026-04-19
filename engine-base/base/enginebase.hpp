#ifndef ENGINEBASE_HPP
#define ENGINEBASE_HPP

#include <string>
#include <unordered_map>

#include "errorbuffer.hpp"

namespace EngineBase
{
    void passExceptionToHost(const EngineError& e);

    std::unordered_map<std::string, std::string> splitArgs(std::string_view input);
}

#endif // ENGINEBASE_HPP
