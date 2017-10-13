#ifndef SPRITETECHNIQUE_H
#define SPRITETECHNIQUE_H

#include "Technique.h"

namespace gfx {

    struct Matrix4x4;
    struct Vector3;

    class SpriteTechnique : public Technique
    {
    public:
        SpriteTechnique();
        virtual ~SpriteTechnique();

        void SetViewProj(const Matrix4x4& m);
        void SetDiffuseTextureUnit(int index);
        void SetEyePos(const Vector3& v);

    private:
        bool OnBuild(GLuint shader_program) override;

        unsigned int gViewProj_location_;
        unsigned int gDiffuseMap_location_;
        unsigned int gEyePos_location_;
    };

}

#endif // SPRITETECHNIQUE_H
