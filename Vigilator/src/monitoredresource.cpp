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
#include "monitoredresource.h"

MonitoredResource::MonitoredResource()
{
    config = new Config();
    healthy = false;
}

void MonitoredResource::setName(std::string name)
{
    this->name = name;
}

std::string MonitoredResource::getName()
{
    return name;
}

void MonitoredResource::setConfig(Config* config)
{
    this->config = config;
}

Config* MonitoredResource::getConfig()
{
    return config;
}

std::deque<MonitoredData*> MonitoredResource::getData()
{
    return data;
}

std::map<std::string, MonitoredPart*> MonitoredResource::getParts()
{
    return parts;
}

void MonitoredResource::decorate(std::string decorator, std::string value)
{
    bool hasDecorator = !decorator.empty();
    if(hasDecorator && !parts[decorator]) {
        parts[decorator] = new MonitoredPart();
    }

    if(hasDecorator) {
        parts[decorator]->addItem(value, value);
    }
}

void MonitoredResource::decorate(std::string decorator, std::string key, std::string value)
{
    bool hasDecorator = !decorator.empty();
    if(hasDecorator && config->TYPE == decorator) {
        config->set(key, value);
    } else if(hasDecorator) {
        if(!parts[decorator]) {
            parts[decorator] = new MonitoredPart();
        }
        parts[decorator]->addItem(key, value);
    }
}

/**
 * @brief MonitoredResource::finaliseUpdate
 * truncates the data based on DATA_LIMIT_AMOUNT to conserve memory usage
 */
void MonitoredResource::finaliseUpdate() {
    int diff = data.size() - DATA_LIMIT_AMOUNT;
    if(diff > 0) {
        for(int i = 0; i < diff; i++) {
            data.pop_front();
        }
    }

    counter++;
}

MonitoredResource::~MonitoredResource()
{
    for(std::map<std::string, MonitoredPart*>::const_iterator it = parts.begin(); it != parts.end(); ++it) {
        delete it->second;
    }
    for(MonitoredData* dataEntry : data) {
        delete dataEntry;
    }
    parts.clear();
    data.clear();
}
