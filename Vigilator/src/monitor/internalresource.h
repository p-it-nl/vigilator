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
#ifndef INTERNALRESOURCE_H
#define INTERNALRESOURCE_H

#include "monitoredresource.h"

/**
 * @brief The InternalResource class is a monitored resource that is monitored internally on a server.
 * It is not available on the internet and only accessible on the server it is running on.
 * It therefor will only share its updates with the monitor via an OnboardResource.
 * @see OnboardResource
 */
class InternalResource: public MonitoredResource
{

public:
    InternalResource();

    bool isHealthy();
    std::vector<std::string> getErrors();
    std::vector<std::string> getWarnings();
    void updateStatus();

    ~InternalResource();
};

#endif // INTERNALRESOURCE_H
