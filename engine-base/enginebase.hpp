#ifndef ENGINEBASE_HPP
#define ENGINEBASE_HPP

struct EngineError;

namespace EngineBase
{
    void handleException(const EngineError& e);
}

#endif // ENGINEBASE_HPP
