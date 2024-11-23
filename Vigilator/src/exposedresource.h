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
#ifndef EXPOSEDRESOURCE_H
#define EXPOSEDRESOURCE_H

#include "monitoredresource.h"
#include <QNetworkAccessManager>
#include <QObject>

/**
 * @brief The ExposedResource class is a monitored resource available via internet
 */
class ExposedResource: public MonitoredResource
{
    QNetworkAccessManager* manager;
    std::string resourceMonitorEndpoint;

    const std::string DATA_EMPTY = "Empty";
    const std::string CONFIG_WEB = "Web";
    const std::string KEY_URL = "url";
    const std::string KEY_TITLE = "title";
    const std::string KEY_DATETIME = "datetime";

    const std::string HTML_TITLE = "<title>";

    // FUTURE_WORK: move json serialization, deserialization and processing to json util class
    const QString KEY_JSON_STATUS = "status";
    const QString KEY_JSON_NAME = "name";
    const QString KEY_JSON_ITEMS = "items";
    const QString KEY_JSON_DATETIME = "datetime";

    void replyFinished(QNetworkReply* reply);
    void retrieveUpdateFromResource(std::string url);
    void validateMonitorReply(MonitoredData* repliedData);
    void validateWebReply(MonitoredData* repliedData);
    void handlePotentialError(std::string message, std::string value, std::string condition);
    void validateItem(QString key, QJsonObject items, std::map<std::string, std::string> validationItems);
    void validateDatetimeCondition(MonitoredPart* part, QJsonObject statusEntry);

public:
    ExposedResource();

    bool isHealthy();
    std::vector<std::string> getErrors();
    std::vector<std::string> getWarnings();
    void updateStatus();

    void connectWithNetworkManager(QObject* caller);

    ~ExposedResource();
};

#endif // EXPOSEDRESOURCE_H
