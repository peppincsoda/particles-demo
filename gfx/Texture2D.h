#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "GLApi.h"

#include <memory>
#include <string>

namespace gfx {

    class Texture2D
    {
    public:
        static bool Load(const std::string& path, std::unique_ptr<Texture2D>& texture);
        static void LoadOrDefault(const std::string& path, std::unique_ptr<Texture2D>& texture);

        Texture2D(GLsizei width, GLsizei height, const GLvoid* pixels);
        ~Texture2D();

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;

        Texture2D(Texture2D&&) = delete;
        Texture2D& operator=(Texture2D&&) = delete;

        void Bind(GLenum texture_unit);

    private:
        GLuint texture_obj_;
    };

}

#endif // TEXTURE2D_H
