#include <nlohmann/json.hpp>

#include <IJsonService.hpp>

#include "jsonservice.hpp"

namespace JsonService
{
    static IJsonService::Handle toHandle(const nlohmann::json& reference)
    {
        return IJsonService::Handle(
                   reinterpret_cast<decltype(IJsonService::Handle::data)>(&reference)
               );
    }
}
