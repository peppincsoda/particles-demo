#ifndef GRIDMESH_H
#define GRIDMESH_H

#include "GfxMath.h"
#include "GLApi.h"

#include <vector>

namespace gfx {

    class GridMesh
    {
    public:
        GridMesh(int gaps, float distance);
        ~GridMesh();

        GridMesh(const GridMesh&) = delete;
        GridMesh& operator=(const GridMesh&) = delete;

        GridMesh(GridMesh&&) = default;
        GridMesh& operator=(GridMesh&&) = default;

        void Render();

    private:
        void Initialize();

        int     gaps_;
        float   distance_;

        struct Vertex
        {
            Vector3 Position;
            uint32_t Color;
        };

        std::vector<Vertex> vertices_;

        GLuint vertex_buffer_;
    };
}

#endif // GRIDMESH_H
