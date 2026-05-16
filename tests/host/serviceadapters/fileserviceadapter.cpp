#include <format>

#include <services/IFileService.hpp>

#include "fileservice/debugstream.hpp"
#include "fileservice/fileservice.hpp"
#include "fileservice/fileservicedatabase.hpp"
#include "fileservice/fileserviceoperations.hpp"
#include "fileservice/synchronizedostream.hpp"

#include "fileserviceadapter.hpp"

namespace FileServiceAdapter
{
    std::string getDebugStreamContent()
    {
        return getDebugStreamContent(IFileService::DEBUGSTREAM);
    }

    std::string getDebugStreamContent(const std::filesystem::path& path)
    {
        auto& stream = FileService::getDatabase().getOrCreateWriteStream(path);
        if (!stream.hasStream())
        {
            throw std::runtime_error(std::format("'{}' has no associated stream!", path.c_str()));
        }
        auto* typedStream = dynamic_cast<FileService::DebugStream*>(stream.expose());
        return typedStream->str();
    }

}
