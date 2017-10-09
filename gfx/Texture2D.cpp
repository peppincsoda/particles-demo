#include "Texture2D.h"

namespace gfx {

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
