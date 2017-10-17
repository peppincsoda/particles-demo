#include "PropertiesModel.h"

#include <QIcon>

namespace particle_editor {

    PropertiesModel::PropertiesModel(std::vector<std::unique_ptr<core::PropertyInterface>>&& properties)
        : properties_(std::move(properties))
    {

    }

    PropertiesModel::~PropertiesModel()
    {

    }

    QModelIndex PropertiesModel::index(int row, int column,
                               const QModelIndex&) const
    {
        return createIndex(row, column, nullptr);
    }

    QModelIndex PropertiesModel::parent(const QModelIndex&) const
    {
        return QModelIndex();
    }

    int PropertiesModel::rowCount(const QModelIndex& parent) const
    {
        if (parent.isValid())
            return 0;
        else
            return properties_.size();
    }

    int PropertiesModel::columnCount(const QModelIndex& parent) const
    {
        if (parent.isValid())
            return 0;
        else
            return 2;
    }

    QVariant PropertiesModel::data(const QModelIndex& index, int role) const
    {
        const auto& property = properties_[index.row()];
      
        if (index.column() == 0) {
            if (role == Qt::DisplayRole) {
                return QString::fromStdString(property->Name());
            } else if (role == Qt::DecorationRole) {
                switch (property->Type()) {
                    case core::PropertyType::Boolean:
                        return QIcon(":/images/property_types/boolean.png");
                    case core::PropertyType::Integer:
                        return QIcon(":/images/property_types/integer.png");
                    case core::PropertyType::Double:
                        return QIcon(":/images/property_types/double.png");
                    case core::PropertyType::Script:
                        return QIcon(":/images/property_types/script.png");
                    case core::PropertyType::ImagePath:
                        return QIcon(":/images/property_types/image_path.png");
                    default:
                        break;
                }
            }
        } else if (index.column() == 1) {
            if (role == Qt::DisplayRole || role == Qt::EditRole) {
                return QString::fromStdString(property->Get());
            } else if (role == Roles_Type) {
                return static_cast<int>(property->Type());
            }
        }

        return QVariant();
    }

    bool PropertiesModel::setData(const QModelIndex& index, const QVariant& value, int role)
    {
        auto& property = properties_[index.row()];
        bool changed = false;

        if (index.column() == 1) {
            if (role == Qt::EditRole) {
                const auto s = value.toString().toStdString();
                if (s != property->Get()) {
                    changed = property->Set(s);
                }
            }
        }

        if (changed)
            emit dataChanged(index, index, {role});

        return changed;
    }

    QVariant PropertiesModel::headerData(int section, Qt::Orientation orientation,
                                         int role) const
    {
        if (orientation == Qt::Horizontal) {
            if (role == Qt::DisplayRole) {
                switch (section) {
                case 0:
                    return tr("Name");
                case 1:
                    return tr("Value");
                }
            }
        }

        return QVariant();
    }

    Qt::ItemFlags PropertiesModel::flags(const QModelIndex& index) const
    {
        Qt::ItemFlags flags = Qt::ItemIsEnabled;
        if (index.column() == 1)
            flags |= Qt::ItemIsEditable;
        return flags;
    }

}
