#include "SpriteMesh.h"

namespace gfx {

    SpriteMesh::SpriteMesh()
        : vertices_()
        , vertex_buffer_(0)
    {
        GLFuncs()->glGenBuffers(1, &vertex_buffer_);
    }

    SpriteMesh::~SpriteMesh()
    {
        if (vertex_buffer_ != 0)
            GLFuncs()->glDeleteBuffers(1, &vertex_buffer_);
    }

    void SpriteMesh::Clear()
    {
        vertices_.clear();
    }

    SpriteMesh::Vertex* SpriteMesh::BeginAppend(std::size_t size)
    {
        const auto current_size = vertices_.size();
        vertices_.resize(current_size + size);
        return &vertices_[current_size];
    }

    void SpriteMesh::EndAppend()
    {

    }

    void SpriteMesh::Render()
    {
        auto glFuncs = GLFuncs();

        glFuncs->glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
        glFuncs->glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_DYNAMIC_DRAW);

        glFuncs->glEnableVertexAttribArray(0);
        glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &static_cast<Vertex*>(0)->position);
        glFuncs->glEnableVertexAttribArray(1);
        glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &static_cast<Vertex*>(0)->rotation);
        glFuncs->glEnableVertexAttribArray(2);
        glFuncs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &static_cast<Vertex*>(0)->size);
        glFuncs->glEnableVertexAttribArray(3);
        glFuncs->glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), &static_cast<Vertex*>(0)->color);

        glFuncs->glDrawArrays(GL_POINTS, 0, vertices_.size());

        glFuncs->glDisableVertexAttribArray(3);
        glFuncs->glDisableVertexAttribArray(2);
        glFuncs->glDisableVertexAttribArray(1);
        glFuncs->glDisableVertexAttribArray(0);
    }

}
