#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "EditorView.h"
#include "PropertiesModel.h"

#include "particles/SpriteEmitterSrc.h"

#include <QElapsedTimer>
#include <QTimer>
#include <QMessageBox>

namespace particle_editor {

    MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(std::make_unique<Ui::MainWindow>())
    , editor_view_()
    , elapsed_timer_()
    , last_update_time_(0)
    , timer_(0)
    {
        ui_->setupUi(this);

        editor_view_ = std::make_unique<EditorView>(this);
        setCentralWidget(editor_view_.get());
        connect(ui_->actionToggle_Wireframe, SIGNAL(toggled(bool)),
                editor_view_.get(), SLOT(SetWireframeMode(bool)));

        elapsed_timer_ = std::make_unique<QElapsedTimer>();
        elapsed_timer_->start();

        SetupTree();

        timer_ = new QTimer(this);
        connect(timer_, SIGNAL(timeout()),
                this, SLOT(Update()));
        timer_->start(10);
    }

    MainWindow::~MainWindow()
    {
        timer_->stop();
    }

    void MainWindow::Update()
    {
        const auto current_update_time = elapsed_timer_->elapsed();
        const auto time_delta = static_cast<int>(current_update_time - last_update_time_);
        last_update_time_ = current_update_time;

        const auto speed = static_cast<float>(ui_->horizontalSlider->value()) / ui_->horizontalSlider->maximum();
        const auto scaled_time_delta = static_cast<int>(speed * time_delta);

        editor_view_->AdvanceEffects(current_update_time, scaled_time_delta);
        editor_view_->update();
    }

    void MainWindow::SetupTree()
    {
        if (auto emitter_src = editor_view_->sprite_emitter_src()) {
            properties_model_ = std::make_unique<PropertiesModel>(emitter_src->Properties());

            connect(properties_model_.get(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
                    editor_view_.get(), SLOT(RestartEffects()));

            ui_->treeView->setModel(properties_model_.get());
        }
    }
}
