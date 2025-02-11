#ifndef RESOURCESLIST_H
#define RESOURCESLIST_H

#include <QObject>
#include <QVector>

struct ResourceItem
{
    bool done;
    QString description;
};

class ResourcesList : public QObject
{
    Q_OBJECT
    QVector<ResourceItem> mItems;

public:
    explicit ResourcesList(QObject *parent = nullptr);

    QVector<ResourceItem> items() const;

    bool setItemAt(int index, const ResourceItem &item);

public slots:
    void appendItem();
    void removeCompletedItems();
    void handleUpdate(const QString &result);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();
};

#endif // RESOURCESLIST_H
