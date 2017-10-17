#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>

namespace core {

    class FileSystem
    {
    public:
        explicit FileSystem(const std::string& root_path);
        ~FileSystem();

        FileSystem(const FileSystem&) = delete;
        FileSystem& operator=(const FileSystem&) = delete;

        FileSystem(FileSystem&&) = default;
        FileSystem& operator=(FileSystem&&) = default;

        std::string GetRealPath(const std::string& path) const;
        std::string GetVirtPath(const std::string& path) const;
        bool GetFileAsString(const std::string& path, std::string& content) const;

        const std::string& GetRootPath() const;

    private:
        std::string root_path_;
    };


    void InitFileSystem(const std::string& root_path);
    FileSystem& TheFileSystem();

}

#endif // FILESYSTEM_H
