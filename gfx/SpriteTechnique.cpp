#include "SpriteTechnique.h"
#include "GfxMath.h"

namespace gfx {

    SpriteTechnique::SpriteTechnique()
        : Technique("/shaders/sprite_vertex.glsl",
                    "/shaders/sprite_fragment.glsl",
                    "/shaders/sprite_geometry.glsl")
    {
    }

    SpriteTechnique::~SpriteTechnique()
    {
    }

    bool SpriteTechnique::OnBuild(GLuint shader_program)
    {
        auto glFuncs = GLFuncs();
        gViewProj_location_ = glFuncs->glGetUniformLocation(shader_program, "gViewProj");
        gDiffuseMap_location_ = glFuncs->glGetUniformLocation(shader_program, "gDiffuseMap");
        gEyePos_location_ = glFuncs->glGetUniformLocation(shader_program, "gEyePos");
        return true;
    }

    void SpriteTechnique::SetViewProj(const Matrix4x4& m)
    {
        GLFuncs()->glUniformMatrix4fv(gViewProj_location_, 1, GL_TRUE, &m.m00);
    }

    void SpriteTechnique::SetDiffuseTextureUnit(int index)
    {
        GLFuncs()->glUniform1i(gDiffuseMap_location_, index);
    }

    void SpriteTechnique::SetEyePos(const Vector3& v)
    {
        GLFuncs()->glUniform3fv(gEyePos_location_, 1, &v.x);
    }

}
