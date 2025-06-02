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
#ifndef STATUSUPDATER_H
#define STATUSUPDATER_H

#include "qnetworkaccessmanager.h"
#include "resourcestatus.h"

class StatusUpdater: public QObject
{
    Q_OBJECT
    QNetworkAccessManager* manager;

    const QString URL = "{url to vigilator node - or something similar}";

public:
    explicit StatusUpdater(QObject *parent = {});

    void requestStatus();
    void statusReceived(QNetworkReply* reply);

    signals:
        void updateReady(const QVector<ResourceStatus*> resourceStatusEntries);
};

#endif // STATUSUPDATER_H
