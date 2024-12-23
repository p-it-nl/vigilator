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
#ifndef CONDITIONVALIDATOR_H
#define CONDITIONVALIDATOR_H

#include <string>

class ConditionValidator
{
    bool matchesIsNotCondition(int valueSize, int conditionSize, int positionInCondition, std::string value, std::string condition);
    bool matchesIsEqualCondition(int valueSize, int conditionSize, int positionInCondition, std::string value, std::string condition);
    bool matchesIsBiggerThenCondition(int valueSize, int conditionSize, std::string value, std::string condition);
    bool matchesIsLessThenCondition(int valueSize, int conditionSize, std::string value, std::string condition);
    bool matchesIsBeforeTheCondition(std::string value, int temporalAmount, std::string temporalType);
    bool matchesIsAfterTheCondition(std::string value, int temporalAmount, std::string temporalType);
    std::string trimFirstSpaceIfExists(std::string value);
public:
    bool validate(std::string value, std::string condition);
};

#endif // CONDITIONVALIDATOR_H
