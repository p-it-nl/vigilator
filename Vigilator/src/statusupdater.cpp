/**
 * Copyright (c) p-it
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "statusupdater.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
#include "qnetworkreply.h"
#include "resourcestatus.h"

#include <qjsondocument.h>

StatusUpdater::StatusUpdater(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &StatusUpdater::statusReceived);
}

void StatusUpdater::requestStatus()
{
    manager->get(QNetworkRequest(QUrl(URL)));
}

void StatusUpdater::statusReceived(QNetworkReply* reply)
{
    QVector<ResourceStatus*> resourceStatusEntries;

    QJsonParseError parseError;
    QByteArray bytes = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);

    if (!parseError.error) {
        QJsonArray statusEntries = document.array();
        for (const QJsonValue& v : statusEntries){
            ResourceStatus* resourceStatus = new ResourceStatus();
            resourceStatus->fromJson(v.toObject());
            resourceStatusEntries.push_back(resourceStatus);
        }
    } else {
        qDebug() << "invalid json received on status reply";
    }

    emit updateReady(resourceStatusEntries);
}

