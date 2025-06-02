#ifndef RESOURCEITEMMODEL_H
#define RESOURCEITEMMODEL_H

#include <QAbstractListModel>
#include <QMetaObject>

Q_MOC_INCLUDE("resourceslist.h")

class ResourcesList;

class ResourceItemModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ResourcesList* list READ list WRITE setList CONSTANT);

public:
    Q_INVOKABLE void onItemClicked(int index, const QString &name);
    explicit ResourceItemModel(QObject *parent = nullptr);

    enum {
        HealthyRole = Qt::UserRole,
        NameRole,
        ErrorsRole,
        WarningsRole,
        StateRole
    };
    virtual QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    ResourcesList* list() const;
    void setList(ResourcesList* list);

private:
    ResourcesList* resourcesList;
};

#endif // RESOURCEITEMMODEL_H
