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
#ifndef MONITORSERVICE_H
#define MONITORSERVICE_H

#include "abstractresource.h"

#include <QtQml/qqml.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtCore/qjsonobject.h>

class MonitorAccessManager;

class MonitorService : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(MonitorAccessManager* network READ network CONSTANT)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QQmlListProperty<AbstractResource> resources READ resources)
    Q_CLASSINFO("DefaultProperty", "resources")
    Q_INTERFACES(QQmlParserStatus)
    QML_ELEMENT

public:
    explicit MonitorService(QObject* parent = nullptr);
    ~MonitorService() override = default;

    MonitorAccessManager* network() const;

    QUrl url() const;
    void setUrl(const QUrl& url);

    void classBegin() override;
    void componentComplete() override;

    QQmlListProperty<AbstractResource> resources();

signals:
    void urlChanged();

private:
    QUrl m_url;
    QList<AbstractResource*> m_resources;
    std::shared_ptr<MonitorAccessManager> m_manager;
};

#endif // MONITORSERVICE_H
