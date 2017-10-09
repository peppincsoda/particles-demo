#ifndef SPRITEMESH_H
#define SPRITEMESH_H

#include "GfxMath.h"
#include "GLApi.h"

#include <vector>

namespace gfx {

    class SpriteMesh
    {
    public:
        struct Vertex
        {
            Vector3 position;
            Vector3 rotation;
            Vector2 size;
            uint32_t color;
        };

        SpriteMesh();
        ~SpriteMesh();

        SpriteMesh(const SpriteMesh&) = delete;
        SpriteMesh& operator=(const SpriteMesh&) = delete;

        SpriteMesh(SpriteMesh&&) = default;
        SpriteMesh& operator=(SpriteMesh&&) = default;

        void Clear();

        Vertex* BeginAppend(std::size_t size);
        void EndAppend();

        void Render();

    private:
        std::vector<Vertex> vertices_;

        GLuint vertex_buffer_;
    };

}

#endif // SPRITEMESH_H
