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
#include "monitoraccessmanager.h"

using namespace Qt::StringLiterals;

static constexpr auto contentTypeJson = "application/json"_L1;

static bool httpResponseSuccess(QNetworkReply* reply)
{
    const int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    const bool isReplyError = (reply->error() != QNetworkReply::NoError);

    qDebug() << "Request to" << reply->request().url() << "finished";
    if(isReplyError)
    {
        qDebug() << "Error" << reply->error();
    }
    else
    {
        qDebug() << "HTTP:" << httpStatusCode;
    }

    return (!isReplyError && (httpStatusCode >= 200 && httpStatusCode < 300));
}

MonitorAccessManager::MonitorAccessManager(QObject *parent) : QNetworkAccessManager{parent}
{
}

void MonitorAccessManager::setUrl(const QUrl& url)
{
    m_url = url;
}

bool MonitorAccessManager::sslSupported() const
{
#if QT_CONFIG(ssl)
    return QSslSocket::supportsSsl();
#else
    return false;
#endif
}

void MonitorAccessManager::get(const QString& api, const QUrlQuery& parameters, ResponseCallback callback)
{
    m_url.setPath(api);
    m_url.setQuery(parameters);
    auto request = QNetworkRequest(m_url);
    QNetworkReply* reply = QNetworkAccessManager::get(request);
    QObject::connect(reply, &QNetworkReply::finished, reply, [reply, callback](){
        callback(reply, httpResponseSuccess(reply));
    });
}

