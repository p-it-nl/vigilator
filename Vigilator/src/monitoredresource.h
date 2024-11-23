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
#ifndef MONITOREDRESOURCE_H
#define MONITOREDRESOURCE_H

#include "config.h"
#include "monitoredpart.h"
#include "monitoreddata.h"
#include <map>
#include <deque>
#include <string>
#include <vector>

class MonitoredResource
{
protected:
    MonitoredResource();

    int counter;
    std::string name;
    Config* config;
    std::map<std::string, MonitoredPart*> parts;
    std::deque<MonitoredData*> data;
    bool healthy;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;

    // FUTURE_WORK maybe this should be configurable
    // In order to limit the amount of memory used, monitored data stored on the heap should be limited
    // If data size (time data received) exceeds the limit amount, the data entries are truncated based on first in, first out
    const int DATA_LIMIT_AMOUNT = 20;
    const char WARNING_INDICATION = 'W';

public:
    virtual ~MonitoredResource();

    void setName(std::string name);
    std::string getName();
    void setConfig(Config* config);
    Config* getConfig();
    std::deque<MonitoredData*> getData();
    std::map<std::string, MonitoredPart*> getParts();
    void decorate(std::string decorator, std::string value);
    void decorate(std::string decorator, std::string key, std::string value);
    void finaliseUpdate();

    virtual bool isHealthy() = 0;
    virtual std::vector<std::string> getErrors() = 0;
    virtual std::vector<std::string> getWarnings() = 0;
    virtual void updateStatus() = 0;
};

#endif // MONITOREDRESOURCE_H
