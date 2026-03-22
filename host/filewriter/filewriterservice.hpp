#ifndef FILEWRITERSERVICE_H
#define FILEWRITERSERVICE_H

#include <filesystem>
#include <memory>
#include <span>

class FileWriterService
{
    private:
        static FileWriterService instance;

        std::filesystem::path base;

    protected:
        FileWriterService();

    public:
        static constexpr auto STDOUT = ":stdout:";

        static FileWriterService getInstance();

        static std::filesystem::path getBase();
        static const char* const getBase_cstr();

        static void setBase(const std::filesystem::path& newBase);
        static void setBase_cstr(const char* const newBase);

        static void write(const std::filesystem::path& filename, const std::string& content);
        static void write_cstr(const char* const filename, const char* const content);

        static void writeBinary(const std::filesystem::path& filename, const std::span<const std::byte> data);
        static void writeBinary_cstr(const std::filesystem::path& filename, const void* const data, size_t length);

        static const std::unique_ptr<std::ostream> getStream(const std::filesystem::path& filename);
};

#endif // FILEWRITERSERVICE_H
