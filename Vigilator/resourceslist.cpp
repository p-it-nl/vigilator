#include "resourceslist.h"
#include "qdebug.h"

ResourcesList::ResourcesList(QObject *parent): QObject{parent}
{
    mItems.append({ true, QStringLiteral("Eat something")});
    mItems.append({ false, QStringLiteral("Drink something")});
    mItems.append({ false, QStringLiteral("Program something")});
}

QVector<ResourceItem> ResourcesList::items() const
{
    return mItems;
}

bool ResourcesList::setItemAt(int index, const ResourceItem &item)
{
    if(index < 0 || index >= mItems.size()) {
        return false;
    }

    const ResourceItem &oldItem = mItems.at(index);
    if(item.done == oldItem.done && item.description == oldItem.description) {
        return false;
    }

    mItems[index] = item;

    return true;
}

void ResourcesList::appendItem()
{
    emit preItemAppended();

    ResourceItem item;
    item.done = false;
    mItems.append(item);

    emit postItemAppended();
}

void ResourcesList::removeCompletedItems()
{
    for(int i = 0; i < mItems.size(); i++) {
        if(mItems.at(i).done) {
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        }
    }
}

void ResourcesList::handleUpdate(const QString &result)
{
    qDebug() << "<<--";
    qDebug() << result;

    appendItem();

}


