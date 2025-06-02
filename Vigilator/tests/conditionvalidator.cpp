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
#include <catch2/catch_all.hpp>
#include <src/monitor/conditionvalidator.h>

TEST_CASE("no condition, resulting in false","[conditionvalidator]")
{
    std::string value = "some value";
    std::string condition;

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for value is not, without a value","[conditionvalidator]")
{
    std::string value;
    std::string condition = "!value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(result);
}

TEST_CASE("condition for value is not, with an empty value","[conditionvalidator]")
{
    std::string value = "";
    std::string condition = "!value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(result);
}

TEST_CASE("condition for value is not, with value being equal to condition","[conditionvalidator]")
{
    std::string value = "value";
    std::string condition = "!value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for value is not, with value being unequal to condition","[conditionvalidator]")
{
    std::string value = "mockvalue";
    std::string condition = "!value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for value is not, with value being unequal to condition expecting no caps and receiving caps","[conditionvalidator]")
{
    std::string value = "Value";
    std::string condition = "!value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is equal to, without a value","[conditionvalidator]")
{
    std::string value;
    std::string condition = "==value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is equal to, with empty value","[conditionvalidator]")
{
    std::string value = "";
    std::string condition = "==value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}
TEST_CASE("condition for is equal to, with unequal value","[conditionvalidator]")
{
    std::string value = "somethingelse";
    std::string condition = "==value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is equal to, with equal value","[conditionvalidator]")
{
    std::string value = "value";
    std::string condition = "==value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is equal to, with equal value expecting numbers","[conditionvalidator]")
{
    std::string value = "8";
    std::string condition = "==8";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is equal to, with equal value with condition starting with a space","[conditionvalidator]")
{
    std::string value = "value";
    std::string condition = "== value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is equal to, with unequal value starting with a space and with condition starting with a space","[conditionvalidator]")
{
    std::string value = " value";
    std::string condition = "== value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is equal to, with equal value expecting a number","[conditionvalidator]")
{
    std::string value = "0";
    std::string condition = "==0";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is partial not, without value","[conditionvalidator]")
{
    std::string value;
    std::string condition = "value !value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is partial not, without having is not condition in condition","[conditionvalidator]")
{
    std::string value = "mock";
    std::string condition = "value value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is partial not, with empty value","[conditionvalidator]")
{
    std::string value = "";
    std::string condition = "value !value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is partial not, with value equal","[conditionvalidator]")
{
    std::string value = "value value";
    std::string condition = "value !value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is partial not, with value not equal","[conditionvalidator]")
{
    std::string value = "value mock";
    std::string condition = "value !value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is partial not, with value having different string size","[conditionvalidator]")
{
    std::string value = "valuevalue mock mock";
    std::string condition = "value !value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is partial not, with value continueing after value","[conditionvalidator]")
{
    std::string value = "value mock mock";
    std::string condition = "value !value";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for value is bigger then, without a value","[conditionvalidator]")
{
    std::string value = "";
    std::string condition = "> 80";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for value is bigger then, with a value less then condition","[conditionvalidator]")
{
    std::string value = "10";
    std::string condition = "> 80";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for value is bigger then, with a value equal to condition","[conditionvalidator]")
{
    std::string value = "80";
    std::string condition = "> 80";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for value is bigger then, with a value bigger then condition","[conditionvalidator]")
{
    std::string value = "88";
    std::string condition = "> 80";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for value is bigger then, with a value not a number","[conditionvalidator]")
{
    std::string value = "mock";
    std::string condition = "> 80";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is less then, without a value","[conditionvalidator]")
{
    std::string value;
    std::string condition = "< 40";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is less then, with empty value","[conditionvalidator]")
{
    std::string value = "";
    std::string condition = "< 40";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is less then, with value being bigger then condition","[conditionvalidator]")
{
    std::string value = "44";
    std::string condition = "< 40";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is less then, with value being equal to condition","[conditionvalidator]")
{
    std::string value = "40";
    std::string condition = "< 40";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is less then, with value being less then condition","[conditionvalidator]")
{
    std::string value = "20";
    std::string condition = "< 40";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is not more then given minutes ago, without value","[conditionvalidator]")
{
    std::string value;
    std::string condition = "< 4min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is not more then given minutes ago, with empty value","[conditionvalidator]")
{
    std::string value = "";
    std::string condition = "< 4min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is not more then given minutes ago, with value not being a timestamp","[conditionvalidator]")
{
    std::string value = "mock";
    std::string condition = "< 4min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is not more then given minutes ago, with value a number but not a timestamp","[conditionvalidator]")
{
    std::string value = "4";
    std::string condition = "< 4min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is not more then given minutes ago, with timestamp value being after condition","[conditionvalidator]")
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    now += std::chrono::minutes(8);
    time_t valueT = std::chrono::system_clock::to_time_t(now);
    std::string value = std::to_string(valueT);
    std::string condition = "< 4min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is not more then given minutes ago, with timestamp value being equal to condition","[conditionvalidator]")
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    now += std::chrono::minutes(4);
    time_t valueT = std::chrono::system_clock::to_time_t(now);
    std::string value = std::to_string(valueT);
    std::string condition = "< 4min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is not more then given minutes ago, with timestamp value being before condition","[conditionvalidator]")
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    now += std::chrono::minutes(3);
    time_t valueT = std::chrono::system_clock::to_time_t(now);
    std::string value = std::to_string(valueT);
    std::string condition = "< 4min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is more then given minutes ago, without value","[conditionvalidator]")
{
    std::string value;
    std::string condition = "> 8min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is more then given minutes ago, with empty value","[conditionvalidator]")
{
    std::string value = "";
    std::string condition = "> 8min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is more then given minutes ago, with value not being a timestamp","[conditionvalidator]")
{
    std::string value = "mock";
    std::string condition = "> 8min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is more then given minutes ago, with value a number but not a timestamp","[conditionvalidator]")
{
    std::string value = "4";
    std::string condition = "> 8min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is more then given minutes ago, with timestamp value being after condition","[conditionvalidator]")
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    now += std::chrono::minutes(16);
    time_t valueT = std::chrono::system_clock::to_time_t(now);
    std::string value = std::to_string(valueT);
    std::string condition = "> 8min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(true == result);
}

TEST_CASE("condition for is more then given minutes ago, with timestamp value being equal to condition","[conditionvalidator]")
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    now += std::chrono::minutes(8);
    time_t valueT = std::chrono::system_clock::to_time_t(now);
    std::string value = std::to_string(valueT);
    std::string condition = "> 8min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}

TEST_CASE("condition for is more then given minutes ago, with timestamp value being before condition","[conditionvalidator]")
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    now += std::chrono::minutes(4);
    time_t valueT = std::chrono::system_clock::to_time_t(now);
    std::string value = std::to_string(valueT);
    std::string condition = "> 8min";

    ConditionValidator validator = ConditionValidator();
    bool result = validator.validate(value, condition);

    REQUIRE(false == result);
}
