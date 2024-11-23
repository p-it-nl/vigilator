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
#include "monitorresource.h"
#include "util.h"
#include "monitoraccessmanager.h"
#include "notifier.h"
#include <QtNetwork/qnetworkreply.h>
#include <QtCore/qurlquery.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

using namespace Qt::StringLiterals;

MonitorResource::MonitorResource(QObject* parent)
    : AbstractResource(parent)
{
    m_data = "UNKNOWN";
}

QString MonitorResource::data() const
{
    return m_data;
}

void MonitorResource::refreshStatus()
{
    MonitorAccessManager::ResponseCallback callback = [this](QNetworkReply* reply, bool success) {
        if (success)
        {
            refreshRequestFinished(reply);
        }
        else
        {
            qDebug() << reply->errorString();
        }
    };
    QUrlQuery query;
    m_manager->get(m_path, query, callback);
}

void MonitorResource::refreshRequestFinished(QNetworkReply* reply)
{
    QByteArray responseBody = reply->readAll();

    std::string str = responseBody.toStdString();
    std::string substr = "ACTIVE";

    int count=0;
    for (int i = 0; i <str.size()-1; i++)
    {
        int m = 0;
        int n = i;
        for (int j = 0; j < substr.size(); j++)
        {
            if (str[n] == substr[j])
            {
                m++;
            }
            n++;
        }
        if (m == substr.size())
        {
            count++;
        }
    }
    qDebug() << "count: ";
    qDebug() << count;

    if(count != 8) {
        qDebug() << "notifiying";
        Notifier().setNotification("Vigilator");
    }

    m_data = QString::fromStdString(str);

    responseBody.rbegin();

    std::optional<QJsonObject> json = toJson(responseBody);
    if (json) {
        m_data = "environment: ";
        m_data.append(json->value("environment").toString());

        QJsonArray status = json->value("status").toArray();
        foreach (const QJsonValue& v, status){
            QJsonObject statusObject = v.toObject();

            QString name = statusObject.value("name").toString();

            m_data.append("\n");
            m_data.append(statusObject.value("name").toString());
            m_data.append(" has: ");
            QJsonObject items = statusObject.value("items").toObject();
            // use items
        }
    }
    else
    {
        m_data = "NOK request failed:";
        m_data.append("\nnot json, but is: \n");
        m_data.append(reply->readAll().toStdString());
        qDebug() << "not json";
    }

    emit dataUpdated();
}


