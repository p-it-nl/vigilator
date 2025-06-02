#ifndef RESOURCESTATUS_H
#define RESOURCESTATUS_H

#include <qstring.h>
#include <qlist.h>
#include <QJsonObject>

class ResourceStatus
{
    QString name;
    QVector<QString> errors;
    QVector<QString> warnings;
    bool healthy;
    QString state;

    const QString KEY_NAME = "name";
    const QString KEY_ERRORS = "errors";
    const QString KEY_WARNINGS = "warnings";
    const QString KEY_HEALTHY = "healthy";

    const QString STATE_OK = "ok";
    const QString STATE_WARNING = "warning";
    const QString STATE_ERROR = "error";

public:
    ResourceStatus();

    QString getName();
    QVector<QString> getErrors();
    QVector<QString> getWarnings();
    QString getState();
    bool isHealthy();

    void fromJson(QJsonObject statusEntry);
};

#endif // RESOURCESTATUS_H
