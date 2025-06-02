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
#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config
{
    bool active;
    std::string endpoint;

    const std::string KEY_ACTIVE = "active";
    const std::string VALUE_ACTIVE = "true";
    const std::string KEY_ENDPOINT = "url";

public:
    Config();
    ~Config();

    const std::string TYPE = "Config";

    void setActive(bool active);
    bool isActive();
    void setEndpoint(std::string endpoint);
    std::string getEndpoint();
    void set(std::string key, std::string value);
};

#endif // CONFIG_H
