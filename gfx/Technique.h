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

        //! Build shader program.
        bool Build();

        //! Activate shader for rendering.
        void Use();

    protected:
        virtual bool OnBuild(GLuint shader_program);

    private:
        std::string vs_file_name_;
        std::string fs_file_name_;
        std::string gs_file_name_;

        GLuint shader_program_;
        GLuint vertex_shader_;
        GLuint geometry_shader_;
        GLuint fragment_shader_;
    };

}

#endif // TECHNIQUE_H
