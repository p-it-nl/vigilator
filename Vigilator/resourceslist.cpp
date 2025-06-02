#include "resourceslist.h"
#include "qdebug.h"

#include "src/resourcestatus.h"

ResourcesList::ResourcesList(QObject *parent): QObject{parent}
{
}

QMap<QString, ResourceStatus*> ResourcesList::getItems() const
{
    return items;
}

QVector<ResourceStatus*> ResourcesList::getSortedItems() const
{
    QVector<ResourceStatus*> sortedItems = QVector<ResourceStatus*>();
    QVector<ResourceStatus*> endItems = QVector<ResourceStatus*>();

    foreach(ResourceStatus* statusEntry, items.values()) {
        if(!statusEntry->isHealthy()) {
            sortedItems.push_front(statusEntry);
        } else if(!statusEntry->getWarnings().isEmpty()) {
            sortedItems.push_back(statusEntry);
        } else {
            endItems.push_back(statusEntry);
        }
    }
    foreach(ResourceStatus* endItem, endItems) {
        sortedItems.push_back(endItem);
    }

    return sortedItems;
}

void ResourcesList::updateItem(QString name, ResourceStatus* item)
{
    if(items.contains(name)) {
        items[name] = item;
    }
}

void ResourcesList::appendItem(QString name, ResourceStatus* resourceStatus)
{
    items.insert(name, resourceStatus);
}

void ResourcesList::removeItem(QString name)
{
    if(items.contains(name)) {
        items.remove(name);
    }
}

void ResourcesList::handleUpdate(const QVector<ResourceStatus*> resourceStatusEntries)
{
    QVector<QString> touched = QVector<QString>();
    foreach(ResourceStatus* statusEntry, resourceStatusEntries) {
        QString name = statusEntry->getName();
        if(items.contains(name)) {
            updateItem(name, statusEntry);
            touched.push_back(name);
        } else {
            appendItem(name, statusEntry);
            touched.push_back(name);
        }
    }
    foreach(QString key, items.keys()) {
        if(!touched.contains(key)) {
            removeItem(key);
        }
    }

    emit itemsUpdated();
}
