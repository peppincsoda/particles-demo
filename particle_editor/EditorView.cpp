#include "EditorView.h"

#include "particles/SpriteEmitterSrc.h"
#include "particles/SpriteEmitterType.h"
#include "particles/SpriteEmitter.h"

#include "gfx/GLApi.h"
#include "gfx/Camera.h"
#include "gfx/CommonTechnique.h"
#include "gfx/GridMesh.h"
#include "gfx/Texture2D.h"
#include "gfx/SpriteTechnique.h"
#include "gfx/SpriteMesh.h"

#include <QMouseEvent>
#include <QMessageBox>
#include <QApplication>

#include <QOpenGLFunctions_3_2_Core>

//! These exports are needed to turn on 3D accelerated graphics on computers having multiple adapters.
extern "C" {
    //! For NVIDIA
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    //! For AMD
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

namespace particle_editor {

    EditorView::EditorView(QWidget* parent)
        : QOpenGLWidget(parent)
        , camera_()
        , common_technique_()
        , grid_mesh_()
        , sprite_emitter_src_(std::make_unique<particles::SpriteEmitterSrc>())
        , sprite_emitter_type_()
        , sprite_emitter_()
        , sprite_technique_()
        , sprite_mesh_()
        , wireframe_mode_(false)
        , last_position_()
    {
    }

    EditorView::~EditorView()
    {

    }

    void EditorView::initializeGL()
    {
        auto* f = QOpenGLContext::currentContext()->versionFunctions<gfx::GLFunctions>();

        gfx::SetGLFuncs(f);

        common_technique_ = std::make_unique<gfx::CommonTechnique>();
        sprite_technique_ = std::make_unique<gfx::SpriteTechnique>();
        if (!common_technique_->Build() ||
            !sprite_technique_->Build()) {
            QMessageBox::critical(this, "ERROR", "Cannot compile shaders, see the log for details");
            QApplication::quit();
            return;
        }

        camera_ = std::make_unique<gfx::Camera>();
        grid_mesh_ = std::make_unique<gfx::GridMesh>(11, 1);
        sprite_mesh_ = std::make_unique<gfx::SpriteMesh>();

        f->glClearColor(0, 0, 0, 0);

        f->glFrontFace(GL_CW);
        f->glCullFace(GL_BACK);
        f->glEnable(GL_CULL_FACE);

        f->glDepthMask(GL_TRUE);
        f->glEnable(GL_DEPTH_TEST);

        f->glEnable(GL_BLEND);
        f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        f->glBlendColor(1, 1, 1, 1);

        RestartEffects();
    }

    void EditorView::resizeGL(int width, int height)
    {
        auto* f = QOpenGLContext::currentContext()->versionFunctions<gfx::GLFunctions>();

        camera_->lens().set_screen_width(width);
        camera_->lens().set_screen_height(height);

        f->glViewport(0, 0, width, height);
    }

    void EditorView::paintGL()
    {
        auto* f = QOpenGLContext::currentContext()->versionFunctions<gfx::GLFunctions>();

        f->glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode_ ? GL_LINE : GL_FILL);

        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gfx::Matrix4x4 world(gfx::Matrix4x4::Identity);
        gfx::Matrix4x4 view(camera_->GetView());
        gfx::Matrix4x4 proj(camera_->lens().GetProj());

        //=====
        // GRID
        //=====
        gfx::Matrix4x4 world_view_proj(proj * view * world);

        common_technique_->Use();
        common_technique_->SetWorldViewProj(world_view_proj);

        grid_mesh_->Render();

        //========
        // SPRITES
        //========
        gfx::Matrix4x4 view_proj(proj * view);

        sprite_technique_->Use();
        sprite_technique_->SetViewProj(view_proj);
        sprite_technique_->SetDiffuseTextureUnit(0);
        sprite_technique_->SetEyePos(camera_->eye_position());

        sprite_emitter_type_->texture()->Bind(GL_TEXTURE0);

        sprite_mesh_->Clear();
        sprite_emitter_->WriteMesh(*sprite_mesh_);
        sprite_mesh_->Render();
    }

    void EditorView::mousePressEvent(QMouseEvent* event)
    {
        if (event->buttons() | Qt::LeftButton) {
            last_position_ = event->pos();
        }
    }

    void EditorView::mouseMoveEvent(QMouseEvent* event)
    {
        const QPoint diff = event->pos() - last_position_;

        if (event->buttons() | Qt::LeftButton) {
            camera_->AddHorizontalAngle(diff.x() * -0.01f);
            camera_->AddVerticalAngle(diff.y() * -0.01f);
        }

        last_position_ = event->pos();
    }

    void EditorView::wheelEvent(QWheelEvent* event)
    {
        camera_->AddEyeDistance(event->delta() * -0.005f);
    }

    void EditorView::SetWireframeMode(bool on)
    {
        wireframe_mode_ = on;
    }

    void EditorView::AdvanceEffects(int64_t current_time, int time_delta)
    {
        if (sprite_emitter_ != nullptr)
            sprite_emitter_->Update(current_time, time_delta);
    }

    void EditorView::RestartEffects()
    {
        sprite_emitter_type_ = sprite_emitter_src_->Build();
        sprite_emitter_ = std::make_unique<particles::SpriteEmitter>(*sprite_emitter_type_, 0);
    }

    particles::SpriteEmitterSrc* EditorView::sprite_emitter_src()
    {
        return sprite_emitter_src_.get();
    }

}
