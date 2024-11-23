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
#include <src/conditionvalidator.h>

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

   // REQUIRE(result);
}

TEST_CASE("condition for value is not, with an empty value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for value is not, with value being equal to condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for value is not, with value being unequal to condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for value is not, with value being unequal to condition expecting no caps and receiving caps","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
//    REQUIRE(1 == 1);
}


TEST_CASE("condition for is equal to, without a value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is equal to, with empty value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
//    REQUIRE(1 == 1);
}

TEST_CASE("condition for is equal to, with unequal value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is equal to, with equal value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is partial equal to and partial not, without value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for is partial equal to and partial not, with empty value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for is partial equal to and partial not, with value not equal and is","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is partial equal to and partial not, with value equal and is","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is partial equal to and partial not, with value not equal and is not","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is partial equal to and partial not, with value equal and is not","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for value is bigger then, without a value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for value is bigger then, with a value less then condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for value is bigger then, with a value equal to condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
   // REQUIRE(1 == 1);
}

TEST_CASE("condition for value is bigger then, with a value bigger then condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}


TEST_CASE("condition for is not equal to, without a value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is not equal to, with empty value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is not equal to, with unequal value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is not equal to, with equal value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is less then, without a value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for is less then, with value being bigger then condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for is less then, with value being equal to condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
   // REQUIRE(1 == 1);
}

TEST_CASE("condition for is not more then given minutes ago, without value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for is not more then given minutes ago, with empty value","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
  //  REQUIRE(1 == 1);
}

TEST_CASE("condition for is not more then given minutes ago, with value not being a timestamp","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is not more then given minutes ago, with timestamp value being after condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is not more then given minutes ago, with timestamp value being equal to condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}

TEST_CASE("condition for is not more then given minutes ago, with timestamp value being before condition","[conditionvalidator]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    ConditionValidator validator = ConditionValidator();

    validator.validate("a", "b");
 //   REQUIRE(1 == 1);
}
