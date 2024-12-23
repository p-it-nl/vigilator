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
#include <chrono>
#include <iostream>


bool ConditionValidator::validate(std::string value, std::string condition) {
    if(!condition.empty()) {
        bool isValid;
        int valueSize = value.size();
        int conditionSize = condition.size();

        /*
             * misschien enum achtig in een switch
             * case IS_NOT_EQUAL
             *
             * case IS_EQUAL
             *
             * etc..
             *
             *
             *
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
             */

        bool startsWithIsEqualCondition = (condition[0] == '=' && condition[1] == '=');
        if(startsWithIsEqualCondition) {
            return matchesIsEqualCondition(valueSize, conditionSize, 0,  value, condition);
        }

        bool startsWithIsNotCondition = condition[0] == '!';
        if(startsWithIsNotCondition) {
            return matchesIsNotCondition(valueSize, conditionSize, 0,  value, condition);
        }

        bool startsWithBiggerThenCondition = condition[0] == '>';
        if(startsWithBiggerThenCondition) {
            return matchesIsBiggerThenCondition(valueSize, conditionSize, value, condition);
        }

        bool startsWithLessThenCondition = condition[0] == '<';
        if(startsWithLessThenCondition) {
            return matchesIsLessThenCondition(valueSize, conditionSize, value, condition);
        }

        std::size_t positionIsNotCondition = condition.find('!');
        if(positionIsNotCondition != std::string::npos) {
            return matchesIsNotCondition(valueSize, conditionSize, static_cast<int>(positionIsNotCondition),  value, condition);
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
    }

    return false;
}

bool ConditionValidator::matchesIsNotCondition(int valueSize, int conditionSize, int positionInCondition, std::string value, std::string condition) {
    if(valueSize == 0) {
        return true;
    }

    std::string valueToMatch = value.substr(positionInCondition, valueSize);
    std::string conditionToMatch = condition.substr((positionInCondition+1), conditionSize);

    if(valueToMatch == conditionToMatch) {
        return false;
    } else {
        return true;
    }
}

bool ConditionValidator::matchesIsEqualCondition(int valueSize, int conditionSize, int positionInCondition, std::string value, std::string condition) {
    if(valueSize == 0) {
        return false;
    }

    std::string valueToMatch = value.substr(positionInCondition, valueSize);
    std::string conditionToMatch = condition.substr((positionInCondition+2), conditionSize);
    conditionToMatch = trimFirstSpaceIfExists(conditionToMatch);
    if(valueToMatch == conditionToMatch) {
        return true;
    } else {
        return false;
    }
}

bool ConditionValidator::matchesIsBiggerThenCondition(int valueSize, int conditionSize, std::string value, std::string condition) {
    if(valueSize == 0) {
        return false;
    }

    std::string valueToMatch = value.substr(0, valueSize);
    std::string conditionToMatch = condition.substr(1, conditionSize);
    conditionToMatch = trimFirstSpaceIfExists(conditionToMatch);
    try {
        std::size_t temportalMinutesPosition = condition.find("min");
        if(temportalMinutesPosition != std::string::npos) {
            int startPositionTemporalIndicator = static_cast<int>(temportalMinutesPosition);
            std::string temporalAmountString = condition.substr(0, startPositionTemporalIndicator);
            temporalAmountString = temporalAmountString.substr(1);
            temporalAmountString = trimFirstSpaceIfExists(temporalAmountString);
            int temporalAmount = std::stoi(temporalAmountString);

            std::string temporalType = condition.substr(startPositionTemporalIndicator, conditionSize);

            return matchesIsAfterTheCondition(value, temporalAmount, temporalType);
        } else {
            int parsedValue = std::stoi(valueToMatch);
            int parsedCondition = std::stoi(conditionToMatch);

            if(parsedValue > parsedCondition) {
                return true;
            } else {
                return false;
            }
        }
    } catch(std::invalid_argument &e){
        return false;
    } catch(std::out_of_range &e) {
        return false;
    }
}

bool ConditionValidator::matchesIsLessThenCondition(int valueSize, int conditionSize, std::string value, std::string condition) {
    if(valueSize == 0) {
        return false;
    }

    std::string valueToMatch = value.substr(0, valueSize);
    std::string conditionToMatch = condition.substr(1, conditionSize);
    conditionToMatch = trimFirstSpaceIfExists(conditionToMatch);

    try {
        std::size_t temportalMinutesPosition = condition.find("min");
        if(temportalMinutesPosition != std::string::npos) {
            int startPositionTemporalIndicator = static_cast<int>(temportalMinutesPosition);
            std::string temporalAmountString = condition.substr(0, startPositionTemporalIndicator);
            temporalAmountString = temporalAmountString.substr(1);
            temporalAmountString = trimFirstSpaceIfExists(temporalAmountString);
            int temporalAmount = std::stoi(temporalAmountString);

            std::string temporalType = condition.substr(startPositionTemporalIndicator, conditionSize);

            return matchesIsBeforeTheCondition(value, temporalAmount, temporalType);
        } else {
            int parsedValue = std::stoi(valueToMatch);
            int parsedCondition = std::stoi(conditionToMatch);

            if(parsedValue < parsedCondition) {
                return true;
            } else {
                return false;
            }
        }
    } catch(std::invalid_argument &e){
        return false;
    } catch(std::out_of_range &e) {
        return false;
    }
}

bool ConditionValidator::matchesIsBeforeTheCondition(std::string value, int temporalAmount, std::string temporalType)
{
    try {
        time_t datetimeValue = std::stol(value);
        if(datetimeValue > 1000000000) {
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            now += std::chrono::minutes(temporalAmount);
            time_t conditionLimit = std::chrono::system_clock::to_time_t(now);
            if(datetimeValue < conditionLimit) {
                return true;
            } else {
                return false;
            }
        } else {
            // not a valid timestamp format
            return false;
        }
    } catch(std::invalid_argument &e){
        return false;
    } catch(std::out_of_range &e) {
        return false;
    }
}

bool ConditionValidator::matchesIsAfterTheCondition(std::string value, int temporalAmount, std::string temporalType)
{
    try {
        time_t datetimeValue = std::stol(value);
        if(datetimeValue > 1000000000) {
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            now += std::chrono::minutes(temporalAmount);
            time_t conditionLimit = std::chrono::system_clock::to_time_t(now);
            if(datetimeValue > conditionLimit) {
                return true;
            } else {
                return false;
            }
        } else {
            // not a valid timestamp format
            return false;
        }
    } catch(std::invalid_argument &e){
        return false;
    } catch(std::out_of_range &e) {
        return false;
    }
}

std::string ConditionValidator::trimFirstSpaceIfExists(std::string value) {
    if(std::isspace(value[0])) {
        return value.substr(1, value.size());
    } else {
        return value;
    }
}

