#include "services.hpp"
#include "jsonservice.hpp"

namespace JsonService
{
    const IJsonService::Handle get(const char* const tag)
    {
        return jsonService().get(tag);
    }
}
