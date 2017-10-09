#include "GLApi.h"

#include <cassert>

namespace gfx {

    static GLFunctions* glFuncs_ = nullptr;

    void SetGLFuncs(GLFunctions* glFuncs)
    {
        glFuncs_ = glFuncs;
    }

    GLFunctions* GLFuncs()
    {
        assert(glFuncs_ != nullptr);
        return glFuncs_;
    }

}
