#include "resourceitemmodel.h"
#include "resourceslist.h"

ResourceItemModel::ResourceItemModel(QObject *parent)
    : QAbstractListModel(parent), resourcesList(nullptr)
{}

void ResourceItemModel::onItemClicked(int index, const QString &name)
{
    qDebug() << "Item clicked at index:" << index << "name:" << name;
    // Add your logic here
}

int ResourceItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !resourcesList)
        return 0;

    return resourcesList->getSortedItems().size();
}

QVariant ResourceItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !resourcesList)
        return QVariant();

    ResourceStatus* item = resourcesList->getSortedItems().at(index.row());
    switch(role) {
    case HealthyRole:
        return QVariant(item->isHealthy());
    case NameRole:
        return QVariant(item->getName());
    case ErrorsRole:
        return QVariant(item->getErrors());
    case WarningsRole:
        return QVariant(item->getWarnings());
    case StateRole:
        return QVariant(item->getState());
    }

    return QVariant();
}

QHash<int, QByteArray> ResourceItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[HealthyRole] = "healthy";
    roles[NameRole] = "name";
    roles[ErrorsRole] = "errors";
    roles[WarningsRole] = "warnings";
    roles[StateRole] = "state";

    return roles;
}

ResourcesList *ResourceItemModel::list() const
{
    return resourcesList;
}

void ResourceItemModel::setList(ResourcesList* list)
{
    beginResetModel();

    if(resourcesList) {
        resourcesList->disconnect(this);
    }

    resourcesList = list;

    if(resourcesList) {
        connect(resourcesList, &ResourcesList::itemsUpdated, this, [=]() {
            beginResetModel();
            endResetModel();
        });
    }

    endResetModel();
}
