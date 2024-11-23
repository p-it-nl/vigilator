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
#ifndef MONITORACCESSMANAGER_H
#define MONITORACCESSMANAGER_H

#include <QtCore/qurlquery.h>
#include <QtCore/qjsondocument.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtQml/qqml.h>

class MonitorAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
    QML_ANONYMOUS

public:
    explicit MonitorAccessManager(QObject *parent = nullptr);

    void setUrl(const QUrl& url);
    bool sslSupported() const;

    using ResponseCallback = std::function<void(QNetworkReply*, bool)>;
    void get(const QString& api, const QUrlQuery& parameters, ResponseCallback callback);

private:
    QUrl m_url;
};

#endif // MONITORACCESSMANAGER_H
