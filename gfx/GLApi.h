#ifndef GLAPI_H
#define GLAPI_H

#include <QtGui/QOpenGLFunctions_3_3_Core>

namespace gfx {

    using GLFunctions = QOpenGLFunctions_3_3_Core;

    void SetGLFuncs(GLFunctions* glFuncs);
    GLFunctions* GLFuncs();

}

#endif // GLAPI_H
