#include "GfxMath.h"

namespace gfx {

    const Matrix4x4 Matrix4x4::Zero( 0, 0, 0, 0
                                   , 0, 0, 0, 0
                                   , 0, 0, 0, 0
                                   , 0, 0, 0, 0 );

    const Matrix4x4 Matrix4x4::Identity( 1, 0, 0, 0
                                       , 0, 1, 0, 0
                                       , 0, 0, 1, 0
                                       , 0, 0, 0, 1 );

}

