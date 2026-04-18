#ifndef ERRORBUFFER_HPP
#define ERRORBUFFER_HPP

#include <list>
#include <string>

#include <ApiStatusCode.hpp>

#include "errors.hpp"

namespace EngineBase
{
    class ErrorBuffer
    {
        public:
            struct ErrorData
            {
                ApiStatusCode errorCode;
                std::string   errorMessage;

                ErrorData() = default;
                ErrorData(ApiStatusCode errorCode, std::string errorMessage);
            };

        private:
            std::list<ErrorData> errors;

        public:
            ErrorBuffer() = default;

            const std::list<ErrorData>& getErrors() const;
            bool isClean() const;
            std::string compileErrorMessage() const;

            void append(ApiStatusCode errorCode, const std::string_view errorMessage);
            void append(const EngineError& error);
            void append(const std::exception& error);

            // TODO: filterByCode and fancy shit
    };

} // namespace EngineBase

#endif // ERRORBUFFER_HPP
