#ifndef PROPERTIESTREEVIEW_H
#define PROPERTIESTREEVIEW_H

#include <QTreeView>

#include <memory>

namespace particle_editor {

    class PropertiesTreeView : public QTreeView
    {
        Q_OBJECT

    public:
        explicit PropertiesTreeView(QWidget* parent = nullptr);
        ~PropertiesTreeView();

    protected:
        void mousePressEvent(QMouseEvent* event) override;
    };

}


#endif // PROPERTIESTREEVIEW_H
