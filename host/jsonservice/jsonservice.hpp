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
     * parse(string) -> json
     * public parseAndRegister(tag, string)
     * read(file)    -> json
     * public readAndRegister(tag, file)
     * validate(json, json) -> json
     * validate(json, tag)  -> json
     * patch(json, json) -> json
     * merge_patch(json, json)?  -> json
     *
     * readValidateAndPatch(file, json)
     * parseValidateAndPatch(file, json)
     * public readValidateAndPatch(file, tag)
     * public parseValidateAndPatch(file, tag)
     *
     * json ops:
     * getHandle(tag) -> Handle
     * getHandleFromPath(tag, path) -> Handle
     * getElement(Handle, item) -> Handle
     * emplace(Handle, path, *) -> Handle
     * asString(Handle), ...
     *
     * json schema builder ops:
     * ???
     */
}

#endif // JSONSERVICE_HPP
