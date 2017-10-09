#include "GridMesh.h"

namespace gfx {

    GridMesh::GridMesh(int gaps, float distance)
        : gaps_(gaps)
        , distance_(distance)
        , vertices_()
        , vertex_buffer_(0)
    {
        Initialize();
    }

    GridMesh::~GridMesh()
    {
        if (vertex_buffer_ != 0)
            GLFuncs()->glDeleteBuffers(1, &vertex_buffer_);
    }

    void GridMesh::Initialize()
    {
        const auto half_size = distance_ * gaps_ * 0.5f;
        const auto grid_y = 0.0f;

        // grid
        for (int i = 0; i <= gaps_; ++i) {
            const float position = -half_size + distance_ * i;

            vertices_.push_back({{position, grid_y, -half_size}, 0xffffffff});
            vertices_.push_back({{position, grid_y,  half_size}, 0xffffffff});

            vertices_.push_back({{-half_size, grid_y, position}, 0xffffffff});
            vertices_.push_back({{ half_size, grid_y, position}, 0xffffffff});
        }

        // coordinate axes
        vertices_.push_back({{0, 0, 0}, 0xff0000ff});
        vertices_.push_back({{1, 0, 0}, 0xff0000ff});
        vertices_.push_back({{0, 0, 0}, 0xff00ff00});
        vertices_.push_back({{0, 1, 0}, 0xff00ff00});
        vertices_.push_back({{0, 0, 0}, 0xffff0000});
        vertices_.push_back({{0, 0, 1}, 0xffff0000});

        auto glFuncs = GLFuncs();
        glFuncs->glGenBuffers(1, &vertex_buffer_);
        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
        glFuncs->glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);
    }

    void GridMesh::Render()
    {
        auto glFuncs = GLFuncs();

        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
        glFuncs->glEnableVertexAttribArray(0);
        glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glFuncs->glEnableVertexAttribArray(1);
        glFuncs->glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), &static_cast<Vertex*>(0)->Color);

        glFuncs->glDrawArrays(GL_LINES, 0, vertices_.size());

        glFuncs->glDisableVertexAttribArray(1);
        glFuncs->glDisableVertexAttribArray(0);
    }

}
