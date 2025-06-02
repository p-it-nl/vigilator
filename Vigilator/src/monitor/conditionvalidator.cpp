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
#include <stdexcept>

bool ConditionValidator::validate(std::string value, std::string condition) {
    if(!condition.empty()) {
        int valueSize = value.size();
        int conditionSize = condition.size();
        int conditionStart = std::isspace(condition[0]) ? 1 : 0;
        char firstChar = condition[conditionStart];

        switch(firstChar) {
        case '!':
            return matchesIsNotCondition(valueSize, conditionSize, conditionStart,  value, condition);
            break;
        case '>':
            return matchesValueCondition(valueSize, conditionSize, value, condition, BIGGER);
            break;
        case '<':
            return matchesValueCondition(valueSize, conditionSize, value, condition, SMALLER);
            break;
        case '=':
            if(condition[1] == '=') {
                return matchesIsEqualCondition(valueSize, conditionSize, conditionStart,  value, condition);
            }
            break;
        default:
            std::size_t positionIsNotCondition = condition.find('!');
            if(std::string::npos != positionIsNotCondition) {
                return matchesIsNotCondition(valueSize, conditionSize, static_cast<int>(positionIsNotCondition),  value, condition);
            }
            break;
        }
    }

    return false;
}

bool ConditionValidator::matchesIsNotCondition(int valueSize, int conditionSize, int positionInCondition, std::string value, std::string condition) {
    if(valueSize == 0) {
        return true;
    }

    std::string valueToMatch = value.substr(positionInCondition, valueSize);
    std::string conditionToMatch = condition.substr((positionInCondition+1), conditionSize);

    return valueToMatch != conditionToMatch;
}

bool ConditionValidator::matchesIsEqualCondition(int valueSize, int conditionSize, int positionInCondition, std::string value, std::string condition) {
    if(valueSize == 0) {
        return false;
    }

    std::string valueToMatch = value.substr(positionInCondition, valueSize);
    std::string conditionToMatch = condition.substr((positionInCondition+2), conditionSize);
    conditionToMatch = trimFirstSpaceIfExists(conditionToMatch);

    return valueToMatch == conditionToMatch;
}

bool ConditionValidator::matchesValueCondition(int valueSize, int conditionSize, std::string value, std::string condition, ConditionType type)
{
    if(valueSize == 0) {
        return false;
    }

    std::string valueToMatch = value.substr(0, valueSize);
    std::string conditionToMatch = condition.substr(1, conditionSize);
    conditionToMatch = trimFirstSpaceIfExists(conditionToMatch);
    try {
        std::size_t temportalMinutesPosition = condition.find("min");
        if(std::string::npos != temportalMinutesPosition) {
            int startPositionTemporalIndicator = static_cast<int>(temportalMinutesPosition);
            std::string temporalAmountString = condition.substr(0, startPositionTemporalIndicator);
            temporalAmountString = temporalAmountString.substr(1);
            temporalAmountString = trimFirstSpaceIfExists(temporalAmountString);
            int temporalAmount = std::stoi(temporalAmountString);

            std::string temporalType = condition.substr(startPositionTemporalIndicator, conditionSize);

            if(BIGGER == type) {
                return matchesDateCondition(value, temporalAmount, temporalType, AFTER);
            } else {
                return matchesDateCondition(value, temporalAmount, temporalType, BEFORE);
            }
        } else {
            int parsedValue = std::stoi(valueToMatch);
            int parsedCondition = std::stoi(conditionToMatch);

            if(BIGGER == type) {
                return parsedValue > parsedCondition;
            } else {
                return parsedValue < parsedCondition;
            }
        }
    } catch(std::invalid_argument &e){
        return false;
    } catch(std::out_of_range &e) {
        return false;
    }
}

bool ConditionValidator::matchesDateCondition(std::string value, int temporalAmount, std::string temporalType, ConditionType type)
{
    try {
        time_t datetimeValue = std::stol(value);
        if(1000000000 < datetimeValue) {
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            now += std::chrono::minutes(temporalAmount);
            time_t conditionLimit = std::chrono::system_clock::to_time_t(now);
            if(BEFORE == type) {
                return datetimeValue < conditionLimit;
            } else {
                return datetimeValue > conditionLimit;
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

