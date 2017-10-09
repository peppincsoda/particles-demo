#include "Technique.h"

#include "filesys/FileSystem.h"

#include <cassert>

#include <QDebug>

namespace gfx {

    static bool LoadShaderFromFile(const std::string& file_name, GLenum shader_type, GLuint& shader_obj)
    {
        auto glFuncs = GLFuncs();
        shader_obj = glFuncs->glCreateShader(shader_type);
        if (shader_obj == 0)
            return false;

        std::string source(filesys::TheFileSystem().GetFileAsString(file_name));
        const GLchar* sources[1];
        sources[0] = source.c_str();
        GLint lengths[1];
        lengths[0] = source.length();

        glFuncs->glShaderSource(shader_obj, 1, sources, lengths);
        glFuncs->glCompileShader(shader_obj);

        GLint status = GL_FALSE;
        glFuncs->glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE)
        {
            char buffer[1024];
            glFuncs->glGetShaderInfoLog(shader_obj, sizeof(buffer), 0, buffer);
            // TODO:
            qDebug() << "Error while compiling shader '" << file_name.c_str() << "':\n" << buffer;
            assert(0);
            return false;
        }

        return true;
    }

    Technique::Technique(const std::string& vs_file_name,
                         const std::string& fs_file_name,
                         const std::string& gs_file_name)
        : shader_program_(0)
        , vertex_shader_(0)
        , geometry_shader_(0)
        , fragment_shader_(0)
    {
        auto glFuncs = GLFuncs();
        shader_program_ = glFuncs->glCreateProgram();

        LoadShaderFromFile(vs_file_name, GL_VERTEX_SHADER, vertex_shader_);
        LoadShaderFromFile(fs_file_name, GL_FRAGMENT_SHADER, fragment_shader_);
        if (!gs_file_name.empty())
            LoadShaderFromFile(gs_file_name, GL_GEOMETRY_SHADER, geometry_shader_);

        glFuncs->glAttachShader(shader_program_, vertex_shader_);
        glFuncs->glAttachShader(shader_program_, fragment_shader_);
        if (geometry_shader_ != 0)
            glFuncs->glAttachShader(shader_program_, geometry_shader_);

        glFuncs->glLinkProgram(shader_program_);

        GLint status = GL_FALSE;
        glFuncs->glGetProgramiv(shader_program_, GL_LINK_STATUS, &status);
        if (status != GL_TRUE)
        {
            char buffer[1024];
            glFuncs->glGetProgramInfoLog(shader_program_, sizeof(buffer), 0, buffer);
            // TODO:
            qDebug() << "Error while linking shader program:\n" << buffer;
            assert(0);
        }
    }

    Technique::~Technique()
    {
        auto glFuncs = GLFuncs();
        if (fragment_shader_ != 0)
            glFuncs->glDeleteShader(fragment_shader_);
        if (geometry_shader_ != 0)
            glFuncs->glDeleteShader(geometry_shader_);
        if (vertex_shader_ != 0)
            glFuncs->glDeleteShader(vertex_shader_);
        if (shader_program_ != 0)
            glFuncs->glDeleteProgram(shader_program_);
    }

    void Technique::Use()
    {
        GLFuncs()->glUseProgram(shader_program_);
    }


}
