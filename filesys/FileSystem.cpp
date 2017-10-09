#include "FileSystem.h"

#include <fstream>
#include <memory>
#include <cassert>

namespace filesys {

    FileSystemException::FileSystemException(const std::string& message)
        : message_(message)
    {
    }

    const char* FileSystemException::what() const noexcept
    {
        return message_.c_str();
    }

    FileSystem::FileSystem(const std::string& root_path)
        : root_path_(root_path)
    {

    }

    FileSystem::~FileSystem()
    {

    }

    std::string FileSystem::GetRealPath(const std::string& path) const
    {
        return root_path_ + path;
    }

    std::string FileSystem::GetFileAsString(const std::string& path) const
    {
        std::ifstream stream(GetRealPath(path));
        if (stream.fail()) {
            throw FileSystemException(std::string("Cannot open file: ") + path);
        }

        std::string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        return content;
    }


    static std::unique_ptr<FileSystem> the_file_system_;

    void InitFileSystem(const std::string& root_path)
    {
        the_file_system_ = std::make_unique<FileSystem>(root_path);
    }

    FileSystem& TheFileSystem()
    {
        assert(the_file_system_.get() != nullptr && "File system must be initialized with InitFileSystem first");

        return *the_file_system_;
    }

}
