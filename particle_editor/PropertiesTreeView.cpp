#include "PropertiesTreeView.h"
#include "PropertiesModel.h"

#include "core/FileSystem.h"

#include <QMouseEvent>
#include <QFileDialog>

namespace particle_editor {

    PropertiesTreeView::PropertiesTreeView(QWidget* parent)
        : QTreeView(parent)
    {
        setRootIsDecorated(false);
    }

    PropertiesTreeView::~PropertiesTreeView()
    {

    }

    void PropertiesTreeView::mousePressEvent(QMouseEvent* event)
    {
        auto handled = false;

        if (auto* m = model()) {
            if (event->button() == Qt::LeftButton) {
                const auto index = indexAt(event->pos());
                const Qt::ItemFlags neededFlags = Qt::ItemIsEditable | Qt::ItemIsEnabled;
                if ((m->flags(index) & neededFlags) == neededFlags) {

                    const auto property_type = static_cast<core::PropertyType>(
                        index.data(PropertiesModel::Roles_Type).toInt());
                    if (property_type == core::PropertyType::ImagePath) {
                        const auto file_name = QFileDialog::getOpenFileName(nullptr,
                            tr("Open Image"),
                            QString::fromStdString(core::TheFileSystem().GetRootPath()),
                            tr("Image Files (*.png)"));

                        const auto virt_path = core::TheFileSystem().GetVirtPath(file_name.toStdString());
                        if (!virt_path.empty())
                            m->setData(index, QString::fromStdString(virt_path));
                    } else {
                        edit(index);
                    }
                    handled = true;
                }
            }
        }

        if (!handled)
            QTreeView::mousePressEvent(event);
    }
}
