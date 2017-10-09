#ifndef COMMONTECHNIQUE_H
#define COMMONTECHNIQUE_H

#include "Technique.h"

namespace gfx {

    struct Matrix4x4;

    class CommonTechnique : public Technique
    {
    public:
        CommonTechnique();

        void SetWorldViewProj(const Matrix4x4& wvp);

    private:
        GLuint gWorldViewProj_location_;
    };

}

#endif // COMMONTECHNIQUE_H
