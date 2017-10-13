#include "Texture2D.h"

#include "core/FileSystem.h"
#include "core/Logger.h"

#include <QImage>

#include <cassert>

namespace gfx {

    static const std::string default_texture_ = "/textures/white-ink-spot-md.png";

    bool Texture2D::Load(const std::string& path, std::unique_ptr<Texture2D>& texture)
    {
        QImage image;

        const auto real_path = core::TheFileSystem().GetRealPath(path);
        if (!image.load(real_path.c_str())) {
            LOG_WARNING("Failed to load image: '%s'", real_path.c_str());
            return false;
        }

        const auto format = image.format();
        if (format != QImage::Format_ARGB32) {
            LOG_WARNING("Non-ARGB32 image format: '%s'", real_path.c_str());
            return false;
        }

        texture = std::make_unique<gfx::Texture2D>(image.width(),
                                                   image.height(),
                                                   image.bits());
        return true;
    }

    void Texture2D::LoadOrDefault(const std::string& path, std::unique_ptr<Texture2D>& texture)
    {
        if (!Load(path, texture)) {
            if (!Load(default_texture_, texture)) {
                assert(0 && "Default texture cannot be loaded");
            }
        }
    }

    Texture2D::Texture2D(GLsizei width, GLsizei height, const GLvoid* pixels)
    {
        auto glFuncs = GLFuncs();

        const GLenum target = GL_TEXTURE_2D;

        glFuncs->glGenTextures(1, &texture_obj_);
        glFuncs->glBindTexture(target, texture_obj_);

        glFuncs->glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glFuncs->glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFuncs->glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFuncs->glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glFuncs->glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    Texture2D::~Texture2D()
    {
        if (texture_obj_ != 0)
            GLFuncs()->glDeleteTextures(1, &texture_obj_);
    }

    void Texture2D::Bind(GLenum texture_unit)
    {
        auto glFuncs = GLFuncs();

        const GLenum target = GL_TEXTURE_2D;

        glFuncs->glActiveTexture(texture_unit);
        glFuncs->glBindTexture(target, texture_obj_);
    }
}
