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
#ifndef MONITOREDRESOURCEREADER_H
#define MONITOREDRESOURCEREADER_H

#include "monitoredresource.h"
#include "monitoredresourceconfiguration.h"

#include <list>

#include <memory>

class MonitoredResourceReader
{
    std::list<MonitoredResourceConfiguration*> resourceConfigurations;
    std::list<std::shared_ptr<MonitoredResource>> resources;
    std::shared_ptr<MonitoredResource> current;
    std::string currentDecorator;

    constexpr static unsigned int DEPTH_RESOURCE = 0;
    constexpr static unsigned int DEPTH_RESOURCE_NAME = 1;
    constexpr static unsigned int DEPTH_RESOURCE_PART = 2;
    constexpr static unsigned int DEPTH_RESOURCE_PART_ENTRY = 3;
    constexpr static unsigned int DEPTH_RESOURCE_PART_ITEM = 4;

    const std::string RESOURCE_EXPOSED = "ExposedResource";
    const std::string RESOURCE_ONBOARD = "OnboardResource";
    const std::string RESOURCE_INTERNAL = "InternalResource";
    const std::string DELIMITER_KEY_VALUE = ":";

    void referenceToResource(std::string line, int depth);
    void construct(std::string type);
    void setDecorator(std::string type);
    void decorate(std::string type);

public:
    MonitoredResourceReader();

    void process(MonitoredResourceConfiguration* config);
    std::list<std::shared_ptr<MonitoredResource>> getResources();

    ~MonitoredResourceReader();
};

#endif // MONITOREDRESOURCEREADER_H
