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
#include "monitor.h"
#include "monitoredresourcereader.h"
#include <QDir>
#include <filesystem>

void Monitor::setUp(QObject* caller)
{
    std::string separator = {std::filesystem::path::preferred_separator};
    std::string path;

    qDebug() << IS_ANDROID;

#ifdef Q_OS_ANDROID
    path.append(ANDROID_ASSETS);
    path.append(separator);
    path.append(CONFIGURATION_FILE);
#else
    path.append(BINARY_DIR);
    path.append(separator);
    path.append(RESOURCE_FOLDER);
    path.append(separator);
    path.append(CONFIGURATION_FILE);
#endif

    qDebug() << path;

    try {
        MonitoredResourceReader reader = MonitoredResourceReader();
        reader.process(new MonitoredResourceConfiguration(path));
        resources = reader.getResources();
        for(std::shared_ptr<MonitoredResource> &resource : resources) {
            if (ExposedResource* er = dynamic_cast<ExposedResource*>(resource.get())){
                er->connectWithNetworkManager(caller);
            } else {
                // FUTURE_WORK do connections if necessary for onboard and internal resources
            }
        }
    } catch(std::string e) {
         qDebug() << e;
    } catch(...) {
         qDebug() << "Unexpected exception occurred while reading config file";
    }
}

void Monitor::addResource(std::shared_ptr<MonitoredResource> resource)
{
    resources.push_back(resource);
}

std::list<std::shared_ptr<MonitoredResource>> Monitor::getResources()
{
    return resources;
}

void Monitor::clearResources()
{
    resources.clear();
}

void Monitor::execute()
{
    for(std::shared_ptr<MonitoredResource> resource : resources) {
        if(resource->getConfig()->isActive()) {
            resource->updateStatus();
        }
    }
}

Monitor::~Monitor()
{
}
