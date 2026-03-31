#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <IJsonService.hpp>

namespace JsonService
{
    enum class EntryState {NONEXISTENT, DECLARED, READY};

    IJsonService exportService();

    /* setAllowComments(bool)
     * setAllowExceptions(bool)
     *
     * parse(string)
     * read(file)
     * validate(json, json)
     * patch(json, json)
     * merge_patch(json, json)?
     *
     * readValidateAndPatch(file, json)
     *
     * json ops:
     * getHandle
     * getHandleFromPath
     * emplace(string, string)
     *
     * asString, ...
     *
     */
}

#endif // JSONSERVICE_HPP
