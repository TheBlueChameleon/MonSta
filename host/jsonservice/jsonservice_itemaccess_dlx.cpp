#include <nlohmann/json.hpp>

#include <services/IJsonService.hpp>

#include "errorservice/catchmacros.hpp"

#include "memoryservice/memoryservice.hpp"

#include "handleconverter.hpp"
#include "jsonservice.hpp"
#include "jsonservice_database_dlx.hpp"
#include "jsonservice_itemaccess_dlx.hpp"

using namespace nlohmann;

namespace JsonService
{
    const IJsonServiceTypes::JsonHandle HOST_API_CALL navigateTo_dlx(
        const IJsonServiceTypes::JsonHandle handle,
        const char* const jsonPointer
    )
    {
        try
        {
            assertSaneHandle(handle);
            const auto& base = toOrderedJson(handle);

            assertSaneJsonPointer(jsonPointer);

            if (jsonPointer[0] == '/')
            {
                const auto jptr = ordered_json::json_pointer(jsonPointer);
                const ordered_json& target = base.at(jptr);
                return toJsonHandle(target);
            }
            else
            {
                const auto& target = base.at(jsonPointer);
                return toJsonHandle(target);
            }
        }
        CATCH_EM_ALL(IJsonServiceTypes::JsonHandle(nullptr))
    }

    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL navigateToModifiable_dlx(
        IJsonServiceTypes::ModifiableJsonHandle handle,
        const char* const jsonPointer
    )
    {
        try
        {
            assertSaneHandle(handle);
            auto& base = toModifiableOrderedJson(handle);

            assertSaneJsonPointer(jsonPointer);

            if (jsonPointer[0] == '/')
            {
                const auto jptr = ordered_json::json_pointer(jsonPointer);
                ordered_json& target = base.at(jptr);
                return toModifiableJsonHandle(target);
            }
            else
            {
                auto& target = base.at(jsonPointer);
                return toModifiableJsonHandle(target);
            }
        }
        CATCH_EM_ALL(IJsonServiceTypes::ModifiableJsonHandle(nullptr))
    }

    const bool HOST_API_CALL contains_dlx(const IJsonServiceTypes::JsonHandle handle, const char* const elementName)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.contains(elementName);
        }
        CATCH_EM_ALL(false)
    }

    const IJsonServiceTypes::JsonType HOST_API_CALL getType_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return static_cast<IJsonServiceTypes::JsonType>(base.type());
        }
        CATCH_EM_ALL(IJsonServiceTypes::JsonType::VOID)
    }

    const bool HOST_API_CALL isNull_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_null();
        }
        CATCH_EM_ALL(false)
    }

    const bool HOST_API_CALL isBoolean_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_boolean();
        }
        CATCH_EM_ALL(false)
    }

    const bool HOST_API_CALL isInteger_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_number_integer();
        }
        CATCH_EM_ALL(false)
    }

    const bool HOST_API_CALL isUnsigned_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_number_unsigned();
        }
        CATCH_EM_ALL(false)
    }

    const bool HOST_API_CALL isFloat_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_number_float();
        }
        CATCH_EM_ALL(false)
    }

    const bool HOST_API_CALL isString_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_string();
        }
        CATCH_EM_ALL(false)
    }

    const bool HOST_API_CALL isArray_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_array();
        }
        CATCH_EM_ALL(false)
    }

    const bool HOST_API_CALL isObject_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_object();
        }
        CATCH_EM_ALL(false)
    }

    const bool HOST_API_CALL getAsBool_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_boolean())
            {
                throw ClientRequestError("Client attempted to read non-boolean Json object as boolean");
            }
            return base.get<bool>();
        }
        CATCH_EM_ALL(false)
    }

    const int HOST_API_CALL getAsInteger_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_number_integer())
            {
                throw ClientRequestError("Client attempted to read non-integer Json object as integer");
            }
            return base.get<int>();
        }
        CATCH_EM_ALL(0)
    }

    const unsigned long long HOST_API_CALL getAsUnsigned_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_number_unsigned())
            {
                throw ClientRequestError("Client attempted to read non-unsigned Json object as unsigned");
            }
            return base.get<unsigned long long>();
        }
        CATCH_EM_ALL(0)
    }

    const double HOST_API_CALL getAsFloat_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_number_float())
            {
                throw ClientRequestError("Client attempted to read non-float Json object as float");
            }
            return base.get<double>();
        }
        CATCH_EM_ALL(0)
    }

    const char* const HOST_API_CALL getAsString_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_string())
            {
                throw ClientRequestError("Client attempted to read non-string Json object as string");
            }
            const auto ptr = base.get_ptr<const ordered_json::string_t*>();
            return ptr->data();
        }
        CATCH_EM_ALL("")
    }

    const size_t HOST_API_CALL getArraySize_dlx(const IJsonServiceTypes::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.size();
        }
        CATCH_EM_ALL(-1)
    }

    const IJsonServiceTypes::JsonHandle HOST_API_CALL getArrayItem_dlx(const IJsonServiceTypes::JsonHandle handle, const int index)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_array())
            {
                ErrorService::setError(
                    ApiStatusCode::INVALID_REQUEST_BY_CLIENT,
                    "Client attempted array operation on non-array Json element"
                );
                return IJsonServiceTypes::JsonHandle(nullptr);
            }
            if (index < 0 ||index >= base.size())
            {
                ErrorService::setError(
                    ApiStatusCode::INVALID_REQUEST_BY_CLIENT,
                    "Client attempted array operation with out-of-bounds index "s +
                    std::to_string(index)
                );
                return IJsonServiceTypes::JsonHandle(nullptr);
            }

            return toJsonHandle(base.at(index));
        }
        CATCH_EM_ALL(IJsonServiceTypes::JsonHandle(nullptr))
    }

    void HOST_API_CALL setToNull_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = ordered_json();
        }
        CATCH_EM_ALL()
    }

    void HOST_API_CALL setToBool_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const bool value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_EM_ALL()
    }

    void HOST_API_CALL setToInteger_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const int value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_EM_ALL()
    }

    void HOST_API_CALL setToUnsigned_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const unsigned int value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_EM_ALL()
    }

    void HOST_API_CALL setToFloat_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const double value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_EM_ALL()
    }

    void HOST_API_CALL setToString_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const char* const value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_EM_ALL()
    }

    void HOST_API_CALL setToHandle_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        try
        {
            assertSaneHandle(source);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = toOrderedJson(source);
        }
        CATCH_EM_ALL()
    }

    void HOST_API_CALL setToArray_dlx(
        const IJsonServiceTypes::ModifiableJsonHandle handle,
        const IJsonServiceTypes::JsonHandle source
    )
    {
        try
        {
            if (!isArray_dlx(source))
            {
                throw JsonError("Handle does not contain an array");
            }
            setToHandle_dlx(handle, source);
        }
        CATCH_EM_ALL()
    }

    void HOST_API_CALL setToObject_dlx(
        const IJsonServiceTypes::ModifiableJsonHandle handle,
        const IJsonServiceTypes::JsonHandle source
    )
    {
        try
        {
            if (!isArray_dlx(source))
            {
                throw JsonError("Handle does not contain an object");
            }
            setToHandle_dlx(handle, source);
        }
        CATCH_EM_ALL()
    }

    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL setToParseable_dlx(
        const IJsonServiceTypes::ModifiableJsonHandle handle,
        const char* const source
    )
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = parse(source);
            return toModifiableJsonHandle(base);
        }
        CATCH_EM_ALL(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
    }

    IMemoryService::MemoryBlock HOST_API_CALL dump_dlx(const IJsonServiceTypes::JsonHandle handle, int indent)
    {
        const auto nullMem = IMemoryService::MemoryBlock{nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            std::string text = base.dump(indent);
            return MemoryService::createFromView(text);
        }
        CATCH_EM_ALL(nullMem)
    }
}
