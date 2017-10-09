#ifndef EDITORVIEW_H
#define EDITORVIEW_H

namespace particles {
    class SpriteEmitterType;
    class SpriteEmitter;
}

namespace gfx {
    class Camera;
    class Texture2D;
    class CommonTechnique;
    class GridMesh;
    class SpriteTechnique;
    class SpriteMesh;
}

#include <QOpenGLWidget>

#include <memory>

namespace particle_editor {

    class EditorView : public QOpenGLWidget
    {
        Q_OBJECT

    public:
        explicit EditorView(QWidget* parent = nullptr);
        ~EditorView();

        particles::SpriteEmitterType* sprite_emitter_type();

        void RestartEffects();

    public slots:
        void SetWireframeMode(bool on);
        void AdvanceEffects(int64_t current_time, int time_delta);

    private:
        void initializeGL() override;
        void resizeGL(int width, int height) override;
        void paintGL() override;

        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void wheelEvent(QWheelEvent* event) override;

        std::unique_ptr<gfx::Camera> camera_;
        std::unique_ptr<gfx::CommonTechnique> common_technique_;
        std::unique_ptr<gfx::GridMesh> grid_mesh_;

        std::unique_ptr<particles::SpriteEmitterType> sprite_emitter_type_;
        std::unique_ptr<particles::SpriteEmitter> sprite_emitter_;
        std::unique_ptr<gfx::Texture2D> texture_;
        std::unique_ptr<gfx::SpriteTechnique> sprite_technique_;
        std::unique_ptr<gfx::SpriteMesh> sprite_mesh_;

        bool wireframe_mode_;

        QPoint last_position_;
    };

}

#endif // EDITORVIEW_H
