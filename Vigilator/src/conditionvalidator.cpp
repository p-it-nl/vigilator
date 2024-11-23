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
#include "conditionvalidator.h"
#include <iostream>


bool ConditionValidator::validate(std::string value, std::string condition) {
    if(value.empty() || condition.empty()) {
        return false;
    }

    /*
    std::string receivedValue = items.value(key).toString().toStdString();

    std::cout << ">>--<<" << std::endl;
    std::cout << key.toStdString() << std::endl;
    std::cout << "should validate" << std::endl;
    std::cout << receivedValue << std::endl;
    std::cout << "agianst" << std::endl;
    std::cout << condition << std::endl;
    std::cout << ">>--<<" << std::endl;

    int size = condition.size();
    std::string validateIs;
    for(std::string::size_type i = 0; i < size; i++) {
        if(std::isspace(condition[i])) {
            continue;
        }

        char character = condition[i];
        if(character == '!') {
            validateIs = condition.substr(i, size);
        }
        std::cout << condition[i] << std::endl;
    }
    std::cout << validateIs << std::endl;
    */

    return true;
}
