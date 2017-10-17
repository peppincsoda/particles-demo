#include "FileSystem.h"
#include "Logger.h"

#include <fstream>
#include <memory>
#include <cassert>
#include <cstring>

#include <algorithm>

namespace core {

    static int PathCompare(const std::string& path1, const std::string& path2)
    {
#ifdef _WIN32
        return strcasecmp(path1.c_str(), path2.c_str());
#else
        // For case sensitive file systems
        return strcmp(path1.c_str(), path2.c_str());
#endif // _WIN32
    }

    FileSystem::FileSystem(const std::string& root_path)
        : root_path_(root_path)
    {
        if (!root_path_.empty()) {
            // replace backslashes to slashes
            std::replace_if(std::begin(root_path_), std::end(root_path_),
                            [](auto c) { return c == '\\'; }, '/');

            // remove trailing slash
            if (root_path_[root_path_.size() - 1] == '/')
                root_path_.resize(root_path_.size() - 1);
        }
    }

    FileSystem::~FileSystem()
    {

    }

    std::string FileSystem::GetRealPath(const std::string& path) const
    {
        return root_path_ + path;
    }

    std::string FileSystem::GetVirtPath(const std::string& path) const
    {
        if (PathCompare(root_path_, path.substr(0, root_path_.length())) == 0)
            return path.substr(root_path_.length());
        else
            return std::string();
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

    const std::string& FileSystem::GetRootPath() const
    {
        return root_path_;
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
