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
#ifndef MONITORRESOURCE_H
#define MONITORRESOURCE_H

#include "abstractresource.h"

#include <QtQml/qqml.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtCore/qjsonobject.h>

class MonitorAccessManager;

class MonitorResource : public AbstractResource
{
    Q_OBJECT
    Q_PROPERTY(QString data READ data NOTIFY dataUpdated)
    Q_PROPERTY(QString path MEMBER m_path REQUIRED)
    QML_ELEMENT

public:
    explicit MonitorResource(QObject* parent = nullptr);
    ~MonitorResource() override = default;

    QString data() const;

    Q_INVOKABLE void refreshStatus();

signals:
    void dataUpdated();

private:
    void refreshRequestFinished(QNetworkReply* reply);
    QString m_data;
    QString m_path;
};

#endif // MONITORRESOURCE_H
