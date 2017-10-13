#include "FileSystem.h"
#include "Logger.h"

#include <fstream>
#include <memory>
#include <cassert>

namespace core {

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

    bool FileSystem::GetFileAsString(const std::string& path, std::string& content) const
    {
        std::ifstream stream(GetRealPath(path));
        if (stream.fail()) {
            LOG_WARNING("Cannot open file: %s", path.c_str());
            return false;
        }

        content = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        return true;
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
