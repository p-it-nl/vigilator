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
#include "config.h"
#include <iostream>

Config::Config()
{
    this->active = false;
}

void Config::setActive(bool active)
{
    this->active = active;
}

bool Config::isActive()
{
    return active;
}

void Config::setEndpoint(std::string endpoint)
{
    this->endpoint = endpoint;
}

std::string Config::getEndpoint()
{
    return endpoint;
};

void Config::set(std::string key, std::string value)
{
    if(KEY_ACTIVE == key && VALUE_ACTIVE == value) {
        setActive(true);
    } else if(KEY_ENDPOINT == key) {
        setEndpoint(value);
    } else {
        std::cout << "Unexpected key detected: " << key << " the value will be ignored" << std::endl;
    }
}

Config::~Config()
{

}
