#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <exception>
#include <string>

namespace filesys {

    class FileSystemException : public std::exception
    {
    public:
        explicit FileSystemException(const std::string& message);

        const char* what() const noexcept override;

    private:
        std::string message_;
    };


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
        std::string GetFileAsString(const std::string& path) const;

    private:
        std::string root_path_;
    };


    void InitFileSystem(const std::string& root_path);
    FileSystem& TheFileSystem();

}

#endif // FILESYSTEM_H
