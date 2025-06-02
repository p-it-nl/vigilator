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
#include "monitoreddata.h"

MonitoredData::MonitoredData() {}

MonitoredData::MonitoredData(std::string data)
{
    this->data = data;
    this->take = 0;
}

MonitoredData::MonitoredData(std::string data, int take)
{
    this->data = data;
    this->take = take;
}

MonitoredData::MonitoredData(const MonitoredData &a)
{
    data = a.data;
    take = a.take;
}

std::string MonitoredData::getData()
{
    return data;
};

int MonitoredData::getTake()
{
    return take;
}

long MonitoredData::getTimestamp()
{
    return timestamp;
}

MonitoredData::~MonitoredData()
{
}
