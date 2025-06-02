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
#include <src/monitor/config.h>

TEST_CASE("default config expecting not to be active and having no url","[config]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";

    Config config = Config();

    REQUIRE(expectedActive == config.isActive());
    REQUIRE(expectedUrl == config.getEndpoint());
}

TEST_CASE("set with empty values","[config]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";
    std::string key = "";
    std::string value = "";

    Config config = Config();
    config.set(key, value);

    REQUIRE(expectedActive == config.isActive());
    REQUIRE(expectedUrl == config.getEndpoint());
}

TEST_CASE("set with key but no value","[config]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";
    std::string key = "active";
    std::string value = "";

    Config config = Config();
    config.set(key, value);

    REQUIRE(expectedActive == config.isActive());
    REQUIRE(expectedUrl == config.getEndpoint());
}

TEST_CASE("set with key active but value not true","[config]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";
    std::string key = "active";
    std::string value = "";

    Config config = Config();
    config.set(key, value);

    REQUIRE(expectedActive == config.isActive());
    REQUIRE(expectedUrl == config.getEndpoint());
}

TEST_CASE("set with key active and value true expecting status to be active","[config]")
{
    bool expectedActive = true;
    std::string expectedUrl = "";
    std::string key = "active";
    std::string value = "true";

    Config config = Config();
    config.set(key, value);

    REQUIRE(expectedActive == config.isActive());
    REQUIRE(expectedUrl == config.getEndpoint());
}

TEST_CASE("set with key url and no value expecting no url","[config]")
{
    bool expectedActive = false;
    std::string expectedUrl = "";
    std::string key = "url";
    std::string value = "";

    Config config = Config();
    config.set(key, value);

    REQUIRE(expectedActive == config.isActive());
    REQUIRE(expectedUrl == config.getEndpoint());
}

TEST_CASE("set with key url and value expecting url to be set","[config]")
{
    bool expectedActive = false;
    std::string expectedUrl = "mock";
    std::string key = "url";
    std::string value = "mock";

    Config config = Config();
    config.set(key, value);

    REQUIRE(expectedActive == config.isActive());
    REQUIRE(expectedUrl == config.getEndpoint());
}

TEST_CASE("set both active and url","[config]")
{
    bool expectedActive = true;
    std::string expectedUrl = "mock";
    std::string key = "active";
    std::string value = "true";
    std::string secondKey = "url";
    std::string secondValue = "mock";

    Config config = Config();
    config.set(key, value);
    config.set(secondKey, secondValue);

    REQUIRE(expectedActive == config.isActive());
    REQUIRE(expectedUrl == config.getEndpoint());
}
