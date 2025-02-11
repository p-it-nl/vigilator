#ifndef RESOURCEITEMMODEL_H
#define RESOURCEITEMMODEL_H

#include <QAbstractListModel>
#include <QMetaObject>

Q_MOC_INCLUDE("resourceslist.h")

class ResourcesList;

class ResourceItemModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ResourcesList* list READ list WRITE setList)

public:
    explicit ResourceItemModel(QObject *parent = nullptr);

    enum {
        DoneRole = Qt::UserRole,
        DescriptionRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ResourcesList* list() const;
    void setList(ResourcesList* list);

private:
    ResourcesList* mList;
};

#endif // RESOURCEITEMMODEL_H
