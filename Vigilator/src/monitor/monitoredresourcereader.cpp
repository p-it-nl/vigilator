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
#include "monitoredresourcereader.h"
#include "exposedresource.h"
#include "internalresource.h"
#include "onboardresource.h"
#include <memory>

MonitoredResourceReader::MonitoredResourceReader() {}

void MonitoredResourceReader::process(MonitoredResourceConfiguration* config)
{
    this->resourceConfigurations.push_back(config);

    config->open();

    int depth = 0;
    int line = 1;
    std::vector<std::byte> buff = std::vector<std::byte>();
    try {
        for(std::byte byte : config->getData()) {
            int i = (unsigned int)byte; // FUTURE_WORK: This works with ASCII maybe not unicode?

            if(i == 9) {
                depth++;
            } else if(i == 10) {
                line++;
                if(buff.size() > 1) {
                    std::string entry(reinterpret_cast<const char *>(&buff[0]), (buff.size()-1));
                    referenceToResource(entry, depth);
                } else {
                    // ignoring empty line
                }

                buff.clear();
                buff.begin();
                depth = 0;
            } else {
                buff.push_back(byte);
            }
        }

        if(buff.size() > 0) {
            std::string entry(reinterpret_cast<const char *>(&buff[0]), (buff.size()-1));
            referenceToResource(entry, depth);
        }

        buff.clear();
    } catch(char const* e) {
        throw "line: " + std::to_string(line) + "message: " + e;
    }
}

std::list<std::shared_ptr<MonitoredResource>> MonitoredResourceReader::getResources()
{
    return resources;
}

void MonitoredResourceReader::referenceToResource(std::string entry, int depth)
{
    switch(depth) {
    case DEPTH_RESOURCE:
        construct(entry);
        break;
    case DEPTH_RESOURCE_NAME:
        if(!current) {
            throw "Resource name given outside the context of a resource";
        }
        current->setName(entry);
        break;
    case DEPTH_RESOURCE_PART:
        setDecorator(entry);
        break;
    case DEPTH_RESOURCE_PART_ENTRY:
        decorate(entry);
        break;
    case DEPTH_RESOURCE_PART_ITEM:
        decorate(entry);
        break;
    default:
        throw "Unexpected character detected, tab depth deeper then expected";
    }
}

void MonitoredResourceReader::construct(std::string type)
{
    if(RESOURCE_EXPOSED == type) {
        current = std::make_shared<ExposedResource>(ExposedResource());
    } else if(RESOURCE_ONBOARD == type) {
        current = std::make_shared<OnboardResource>(OnboardResource());
    } else if(RESOURCE_INTERNAL == type) {
        current = std::make_shared<InternalResource>(InternalResource());
    }

    if(current) {
        this->resources.push_back(current);
    }
}

void MonitoredResourceReader::setDecorator(std::string type)
{
    currentDecorator = type;
}

void MonitoredResourceReader::decorate(std::string value)
{
    std::size_t pos = value.find(DELIMITER_KEY_VALUE);

    if(pos) {
        std::string pairKey = value.substr(0, pos);
        std::size_t take;
        if(isspace(value[pos+1])) {
            take = pos + 2;
        } else {
            take = pos + 1;
        }
        std::string pairValue = value.substr(take, value.size());

        current->decorate(currentDecorator, pairKey, pairValue);
    } else {
        current->decorate(currentDecorator, value);
    }
}

MonitoredResourceReader::~MonitoredResourceReader()
{

}
