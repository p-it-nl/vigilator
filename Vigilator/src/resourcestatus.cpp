#include "resourcestatus.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
#include <qjsondocument.h>

ResourceStatus::ResourceStatus() {}

QString ResourceStatus::getName()
{
    return name;
}

QVector<QString> ResourceStatus::getErrors()
{
    return errors;
}

QVector<QString> ResourceStatus::getWarnings()
{
    return warnings;
}

QString ResourceStatus::getState()
{
    return state;
}

bool ResourceStatus::isHealthy()
{
    return healthy;
}

void ResourceStatus::fromJson(QJsonObject json)
{
    name = json.value(KEY_NAME).toString();
    QJsonArray errorsJson = json.value(KEY_ERRORS).toArray();
    for (const QJsonValue& error : errorsJson){
        errors.push_back(error.toString());
    }
    QJsonArray warningsJson = json.value(KEY_WARNINGS).toArray();
    for (const QJsonValue& warning : warningsJson){
        warnings.push_back(warning.toString());
    }
    healthy = json.value(KEY_HEALTHY).toBool(false);
    if(!healthy) {
        state = STATE_ERROR;
    } else if(!warnings.isEmpty()) {
        state = STATE_WARNING;
    } else {
        state = STATE_OK;
    }
}
