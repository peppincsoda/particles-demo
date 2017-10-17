#include "MainWindow.h"
#include "EditorView.h"
#include "EditorLogger.h"
#include "PropertiesModel.h"
#include "PropertiesTreeView.h"

#include "particles/SpriteEmitterSrc.h"
#include "core/FileSystem.h"
#include "core/Logger.h"

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

    static void AddDockWidget(QMainWindow* mainWindow, const QString& objectName, const QString& windowTitle, Qt::DockWidgetArea area, QWidget* widget)
    {
        auto* r = new QDockWidget(QString(), mainWindow);
        r->setObjectName(objectName);
        r->setWindowTitle(windowTitle);
        r->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        r->setWidget(widget);
        mainWindow->addDockWidget(area, r);
    }

    MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , editor_view_(nullptr)
    , editor_logger_(nullptr)
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
        AddLogsDockWidget();
        AddHelpDockWidget();

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

        AddDockWidget(this, "propertiesDockWidget", tr("Properties"), Qt::RightDockWidgetArea, properties_view_);
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

        AddDockWidget(this, "controlsDockWidget", tr("Controls"), Qt::RightDockWidgetArea, w);
    }

    void MainWindow::AddLogsDockWidget()
    {
        auto* text_edit = new QTextEdit(this);
        text_edit->setReadOnly(true);
        AddDockWidget(this, "logsDockWidget", tr("Logs"), Qt::LeftDockWidgetArea, text_edit);

        editor_logger_ = std::make_unique<EditorLogger>(text_edit);
        core::SetLogger(editor_logger_.get());
    }

    void MainWindow::AddHelpDockWidget()
    {
        std::string str;
        if (!core::TheFileSystem().GetFileAsString("/docs/help.html", str))
            return;

        auto* text_edit = new QTextEdit(this);
        text_edit->setReadOnly(true);
        text_edit->insertHtml(QString::fromStdString(str));
        AddDockWidget(this, "helpDockWidget", tr("Help"), Qt::LeftDockWidgetArea, text_edit);
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
