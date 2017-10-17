#include "MainWindow.h"
#include "EditorView.h"
#include "PropertiesModel.h"
#include "PropertiesTreeView.h"

#include "particles/SpriteEmitterSrc.h"

#include <QElapsedTimer>
#include <QTimer>
#include <QMessageBox>
#include <QTextEdit>
#include <QSlider>
#include <QDockWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QPushButton>
#include <QWidget>

namespace particle_editor {

    MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , editor_view_(nullptr)
    , elapsed_timer_(nullptr)
    , last_update_time_(0)
    , timer_(nullptr)
    , properties_model_(nullptr)
    , properties_view_(nullptr)
    , speed_slider_(nullptr)
    {
        setObjectName("mainWindow");
        setWindowTitle(tr("Yet Another Particle Editor"));
        resize(QDesktopWidget().availableGeometry().size() * 0.7);

        editor_view_ = std::make_unique<EditorView>(this);
        setCentralWidget(editor_view_.get());

        if (auto emitter_src = editor_view_->sprite_emitter_src()) {
            properties_model_ = std::make_unique<PropertiesModel>(emitter_src->Properties());
            connect(properties_model_.get(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
                    editor_view_.get(), SLOT(RestartEffects()));
        }

        AddPropertiesDockWidget();
        AddControlsDockWidget();

        elapsed_timer_ = std::make_unique<QElapsedTimer>();
        elapsed_timer_->start();

        timer_ = new QTimer(this);
        connect(timer_, SIGNAL(timeout()),
                this, SLOT(Update()));
        timer_->start(10);
    }

    MainWindow::~MainWindow()
    {
        timer_->stop();
    }

    void MainWindow::AddPropertiesDockWidget()
    {
        properties_view_ = new PropertiesTreeView(this);
        properties_view_->setModel(properties_model_.get());
        properties_view_->setColumnWidth(0, 150);

        auto* r = new QDockWidget(QString(), this);
        r->setObjectName("propertiesDockWidget");
        r->setWindowTitle(tr("Properties"));
        r->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        r->setWidget(properties_view_);
        addDockWidget(Qt::RightDockWidgetArea, r);
    }

    void MainWindow::AddControlsDockWidget()
    {
        speed_slider_ = new QSlider(Qt::Horizontal, this);
        speed_slider_->setValue(speed_slider_->maximum());

        auto* w = new QWidget(this);
        {
            auto* l = new QVBoxLayout;
            {
                auto* speed_row = new QHBoxLayout;
                speed_row->addWidget(new QLabel(tr("Speed:"), this));
                speed_row->addWidget(speed_slider_);
                l->addLayout(speed_row);
            }
            {
                auto* wf_button = new QPushButton(tr("Wireframe"), this);
                wf_button->setCheckable(true);
                connect(wf_button, SIGNAL(toggled(bool)),
                    editor_view_.get(), SLOT(SetWireframeMode(bool)));
                l->addWidget(wf_button);
            }
            w->setLayout(l);
        }

        auto* r = new QDockWidget(QString(), this);
        r->setObjectName("controlsDockWidget");
        r->setWindowTitle(tr("Controls"));
        r->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        r->setWidget(w);
        addDockWidget(Qt::RightDockWidgetArea, r);
    }

    void MainWindow::Update()
    {
        const auto current_update_time = elapsed_timer_->elapsed();
        const auto time_delta = static_cast<int>(current_update_time - last_update_time_);
        last_update_time_ = current_update_time;

        const auto speed = static_cast<float>(speed_slider_->value()) / speed_slider_->maximum();
        const auto scaled_time_delta = static_cast<int>(speed * time_delta);

        editor_view_->AdvanceEffects(current_update_time, scaled_time_delta);
        editor_view_->update();
    }

}
