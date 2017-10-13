#include "CommonTechnique.h"
#include "GfxMath.h"

namespace gfx {

    CommonTechnique::CommonTechnique()
        : Technique("/shaders/common_vertex.glsl",
                    "/shaders/common_fragment.glsl",
                    "")
        , gWorldViewProj_location_(0)
    {
    }

    bool CommonTechnique::OnBuild(GLuint shader_program)
    {
        gWorldViewProj_location_ = GLFuncs()->glGetUniformLocation(shader_program, "gWorldViewProj");
        return true;
    }

    void CommonTechnique::SetWorldViewProj(const Matrix4x4& wvp)
    {
        GLFuncs()->glUniformMatrix4fv(gWorldViewProj_location_, 1, GL_TRUE, &wvp.m00);
    }

}
