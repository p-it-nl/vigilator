#include "resourceitemmodel.h"
#include "resourceslist.h"

ResourceItemModel::ResourceItemModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{}

int ResourceItemModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant ResourceItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const ResourceItem item = mList->items().at(index.row());
    switch(role) {
    case DoneRole:
        return QVariant(item.done);
    case DescriptionRole:
        return QVariant(item.description);
    }

    return QVariant();
}

bool ResourceItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList) {
        return false;
    }

    ResourceItem item = mList->items().at(index.row());
    switch(role) {
    case DoneRole:
        item.done = value.toBool();
        break;
    case DescriptionRole:
        item.description = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ResourceItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ResourceItemModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";

    return names;
}

ResourcesList *ResourceItemModel::list() const
{
    return mList;
}

void ResourceItemModel::setList(ResourcesList *list)
{
    beginResetModel();

    if(mList) {
        mList->disconnect(this);
    }

    mList = list;

    if(mList) {
        connect(mList, &ResourcesList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &ResourcesList::postItemAppended, this, [=]() {
            endInsertRows();
        });
        connect(mList, &ResourcesList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &ResourcesList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
