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
#include "exposedresource.h"
#include "qjsonarray.h"
#include "qnetworkreply.h"
#include <iostream>
#include <qjsondocument.h>
#include <qjsonobject.h>

ExposedResource::ExposedResource(): MonitoredResource()
{
    counter = 0;
}

bool ExposedResource::isHealthy()
{
    return healthy;
}

std::vector<std::string> ExposedResource::getErrors()
{
    return errors;
}

std::vector<std::string> ExposedResource::getWarnings()
{
    return warnings;
}

void ExposedResource::updateStatus()
{
    // TODO: can be a bit prettier then full reset here
    healthy = true;
    errors.clear();

    if(!resourceMonitorEndpoint.empty()) {
        retrieveUpdateFromResource(resourceMonitorEndpoint);
    } else {
        resourceMonitorEndpoint = config->getEndpoint();
    }

    MonitoredPart* webPart = parts[CONFIG_WEB];
    if(webPart) {
        std::string webUrl = webPart->getItems()[KEY_URL];
        if(!webUrl.empty()) {
            retrieveUpdateFromResource(webUrl);
        } else {
            healthy = false;
            errors.push_back("item: Web, no web url provided");
        }
    } else {
        // resource does not require web availability checks
    }


    finaliseUpdate();
}

void ExposedResource::connectWithNetworkManager(QObject* caller)
{
    this->manager = new QNetworkAccessManager(caller);
    QObject::connect(this->manager, &QNetworkAccessManager::finished,
                     caller, [=](QNetworkReply *reply) {
                         replyFinished(reply);
                     }
                     );
}

void ExposedResource::replyFinished(QNetworkReply* reply)
{
    std::string replyUrl = reply->url().toString().toStdString();
    if (reply->error()) {
        healthy = false;

        std::string error = replyUrl + " returned: " + reply->errorString().toStdString();
        errors.push_back(error);
        data.push_back(new MonitoredData(error, counter));
    } else {
        QByteArray answer = reply->readAll();
        if(!answer.isNull() && !answer.isEmpty()) {
            MonitoredData* result = new MonitoredData(answer.toStdString(), counter);
            data.push_back(result);

            if(resourceMonitorEndpoint == replyUrl) {
                validateMonitorReply(result);
            } else {
                validateWebReply(result);
            }
        } else {
            healthy = false;
            std::string error = "no answer received from url " + replyUrl;
            errors.push_back(error);
            data.push_back(new MonitoredData(error, counter));
        }
    }
}

void ExposedResource::retrieveUpdateFromResource(std::string url)
{
    manager->get(QNetworkRequest(QUrl(QString::fromStdString(url))));
}

void ExposedResource::validateMonitorReply(MonitoredData* repliedData)
{
    QJsonParseError parseError;
    QByteArray bytes = QByteArray::fromStdString(repliedData->getData());
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);

    if (!parseError.error) {
        QJsonObject json = document.object();
        QJsonArray status = json.value(KEY_JSON_STATUS).toArray();

        for (const QJsonValue& v : status){
            QJsonObject statusEntry = v.toObject();

            std::string name = statusEntry.value(KEY_JSON_NAME).toString().toStdString();
            if(parts.find(name) != parts.end()) {
                MonitoredPart* part = parts[name];
                std::map<std::string, std::string> validationItems = part->getItems();
                QJsonObject items = statusEntry.value(KEY_JSON_ITEMS).toObject();
                foreach (const QString key, items.keys()){
                    validateItem(key, items, validationItems);
                }

                validateDatetimeCondition(part, statusEntry);
            } else {
                // Not something the resource is interested in monitoring, skipping
            }
        }
    } else {
        errors.push_back("Response data not JSON:" + parseError.errorString().toStdString() + "at " + std::to_string(parseError.offset));
        healthy = false;
    }
}

/**
 * @brief ExposedResource::validateWebReply
 *  Determine if the replied data provides any content and if required, validate the title
 *  IF title is required, currently expects an HTML response, meaning it will check for
 *     the title in a title element, else any response could be accepted as valid, even error pages
 * @param repliedData the replied data
 */
void ExposedResource::validateWebReply(MonitoredData* repliedData)
{
    std::string data = repliedData->getData();
    MonitoredPart* webPart = parts[CONFIG_WEB];

    std::string title = webPart->getItems()[KEY_TITLE];
    if(!title.empty()) {
        std::string needle = HTML_TITLE + title;
        std::size_t found = data.find(needle);
        if(found == std::string::npos) {
            errors.push_back("Web reply for url " + webPart->getItems()[KEY_URL] + " failed to validate title");
            healthy = false;
        }
    } else if(data.length() < 3) {
        errors.push_back("Web reply for url " + webPart->getItems()[KEY_URL] + " resulted in empty response");
        healthy = false;
    }
}

void ExposedResource::validateItem(QString key, QJsonObject items, std::map<std::string, std::string> validationItems) {
    std::string keyString = key.toStdString();
    if(validationItems.find(keyString) != validationItems.end()) {
        std::string condition = validationItems[keyString];
        if(!condition.empty()) {
            // validate wtih condition validator
        } else {
            // Not something the resource is interested in monitoring, skipping
        }
    }
}

// FUTURE_WORK: use the one from conditon validator
void ExposedResource::validateDatetimeCondition(MonitoredPart* part, QJsonObject statusEntry) {
    std::string datetimeCondition = part->getDatetimeCondition();
    if(!datetimeCondition.empty()) {
        time_t datetimeLastUpdated = statusEntry.value(KEY_JSON_DATETIME).toDouble();

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        now += std::chrono::minutes(5);
        time_t conditionLimit = std::chrono::system_clock::to_time_t(now);
        if(datetimeLastUpdated > conditionLimit) {
            handlePotentialError(
                "Received update data exceeds specified time constraints in object " + name,
                ctime(&datetimeLastUpdated), datetimeCondition);
        } else {
            // the update is timely
        }
    } else {
        // for this monitored part, datetime of the update is not required to be within boundaries
    }
}

void ExposedResource::handlePotentialError(std::string message, std::string value, std::string condition) {
    std::cout << condition << std::endl;
    char endingChar = condition.at(condition.size()-1);
    if(WARNING_INDICATION == endingChar) {
        std::cout << "warning: " << message << std::endl;
        warnings.push_back(message);
    } else {
        std::cout << "error: " << message << std::endl;
        errors.push_back(message);
        healthy = false;
    }
}

ExposedResource::~ExposedResource()
{

}
