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
#include "monitoredpart.h"
#include <iostream>

MonitoredPart::MonitoredPart() {}

void MonitoredPart::addItem(std::string item, std::string condition)
{
    if(DATETIME == item) {
        setDatetimeCondition(condition);
    } else if(!item.empty()){
        items[item] = condition;
    }
}

void MonitoredPart::setDatetimeCondition(std::string condition)
{
    datetimeCondition = condition;
}

std::map<std::string, std::string> MonitoredPart::getItems()
{
    return items;
}

std::string MonitoredPart::getDatetimeCondition()
{
    return datetimeCondition;
}

MonitoredPart::~MonitoredPart()
{
    items.clear();
}
