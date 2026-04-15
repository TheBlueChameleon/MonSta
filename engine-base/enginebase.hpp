#ifndef ENGINEBASE_HPP
#define ENGINEBASE_HPP

#include <string>
#include <unordered_map>

struct EngineError;

namespace EngineBase
{
    void handleException(const EngineError& e);

    std::unordered_map<std::string, std::string> splitArgs(std::string_view input);
}

#endif // ENGINEBASE_HPP
