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
#ifndef MONITOREDRESOURCECONFIGURATION_H
#define MONITOREDRESOURCECONFIGURATION_H

#include "fileresource.h"
#include <string>

/**
 * @brief The OnboardResource class is a monitored resource that is onboard a server.
 * It monitors the server itself as well as internal resources that might be running on the server.
 * The onboard resource will send information updates to the monitor at a given interval.
 * @see InternalResource
 */
class MonitoredResourceConfiguration: public FileResource
{
public:
    MonitoredResourceConfiguration(std::string path);

    void open();

    ~MonitoredResourceConfiguration();
};

#endif // MONITOREDRESOURCECONFIGURATION_H
