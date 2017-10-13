#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "EditorView.h"

#include "particles/SpriteEmitterSrc.h"

#include <QElapsedTimer>
#include <QTimer>
#include <QStyledItemDelegate>
#include <QMessageBox>

namespace particle_editor {

    class NoEditDelegate : public QStyledItemDelegate
    {
    public:
        NoEditDelegate(QObject* parent = 0) : QStyledItemDelegate(parent) {}

        virtual QWidget* createEditor(QWidget*, const QStyleOptionViewItem&, const QModelIndex&) const
        {
            return 0;
        }
    };

    MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(std::make_unique<Ui::MainWindow>())
    , editor_view_()
    , elapsed_timer_()
    , last_update_time_(0)
    , timer_(0)
    {
        ui_->setupUi(this);

        // Disable editing for the 0th column
        ui_->treeWidget->setItemDelegateForColumn(0, new NoEditDelegate(ui_->treeWidget));
        connect(ui_->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                this, SLOT(onPropertyChanged(QTreeWidgetItem*,int)));

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
        // Prevent recursion when calling setData
        ui_->treeWidget->blockSignals(true);

        ui_->treeWidget->clear();

        if (auto emitter_src = editor_view_->sprite_emitter_src()) {
            const auto& properties = emitter_src->Properties();
            for (const auto& p : properties) {

                QTreeWidgetItem* item = new QTreeWidgetItem(ui_->treeWidget);
                item->setText(0, p->Name().c_str());
                item->setFlags(item->flags() | Qt::ItemIsEditable);

                item->setData(1, Qt::DisplayRole, QVariant(p->Get().c_str()));

                ui_->treeWidget->addTopLevelItem(item);
            }
        }

        ui_->treeWidget->blockSignals(false);
    }

    void MainWindow::onPropertyChanged(QTreeWidgetItem* item, int column)
    {
        // Prevent recursion when calling setData
        ui_->treeWidget->blockSignals(true);

        if (column == 1) {   //  value column
            if (auto emitter_src = editor_view_->sprite_emitter_src()) {
                const std::string name(item->text(0).toStdString());
                const std::string new_value(item->data(1, Qt::DisplayRole).toString().toStdString());

                // NOTE: This is inefficient, we might use an unordered_map to store the properties
                auto properties = emitter_src->Properties();
                auto it = std::find_if(std::begin(properties), std::end(properties),
                                       [&name](const auto& p) { return p->Name() == name; });
                if (it != std::end(properties)) {
                    if (!(*it)->Set(new_value)) {
                        QMessageBox::warning(this, "WARNING",
                                             QString("Cannot set property %1").arg(name.c_str()));
                        // Revert to the previous value
                        item->setData(1, Qt::DisplayRole, QVariant((*it)->Get().c_str()));
                    } else {
                        editor_view_->RestartEffects();

                        item->treeWidget()->clearSelection();
                    }
                }
            }
        }

        ui_->treeWidget->blockSignals(false);
    }

}
