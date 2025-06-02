#ifndef RESOURCESLIST_H
#define RESOURCESLIST_H

#include <QObject>
#include <QVector>
#include "src/resourcestatus.h"

class ResourcesList : public QObject
{
    Q_OBJECT
    QMap<QString, ResourceStatus*> items;

public:
    explicit ResourcesList(QObject *parent = nullptr);

    QMap<QString, ResourceStatus*> getItems() const;
    QVector<ResourceStatus*> getSortedItems() const;

    void updateItem(QString name, ResourceStatus* item);
    void appendItem(QString name, ResourceStatus* resourceStatus);
    void removeItem(QString name);
    void handleUpdate(const QVector<ResourceStatus*> resourceStatusEntries);

signals:
    void itemsUpdated();
};

#endif // RESOURCESLIST_H
