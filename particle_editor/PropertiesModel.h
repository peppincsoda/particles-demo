#ifndef PROPERTIESMODEL_H
#define PROPERTIESMODEL_H

#include "core/Properties.h"

#include <QAbstractItemModel>

namespace particle_editor {

    class PropertiesModel : public QAbstractItemModel
    {
        Q_OBJECT
        
    public:
        enum Roles
        {
            Roles_Type = Qt::UserRole + 1,
        };

        explicit PropertiesModel(std::vector<std::unique_ptr<core::PropertyInterface>>&& properties);
        ~PropertiesModel();
    
    protected:
        QModelIndex index(int row, int column,
                          const QModelIndex& parent) const override;
        QModelIndex parent(const QModelIndex& child) const override;

        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;

        QVariant data(const QModelIndex& index, int role) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role) override;

        QVariant headerData(int section, Qt::Orientation orientation,
                            int role) const override;

        Qt::ItemFlags flags(const QModelIndex& index) const override;
        
    private:
        std::vector<std::unique_ptr<core::PropertyInterface>> properties_;
    };

}

#endif // PROPERTIESMODEL_H
