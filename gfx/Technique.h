#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include "GLApi.h"

#include <string>

namespace gfx {

    class Technique
    {
    public:
        Technique(const std::string& vs_file_name,
                  const std::string& fs_file_name,
                  const std::string& gs_file_name);
        virtual ~Technique();

        Technique(const Technique&) = delete;
        Technique& operator=(const Technique&) = delete;

        Technique(Technique&&) = default;
        Technique& operator=(Technique&&) = default;

        void Use();

    protected:
        GLuint shader_program_;
        GLuint vertex_shader_;
        GLuint geometry_shader_;
        GLuint fragment_shader_;
    };

}

#endif // TECHNIQUE_H
