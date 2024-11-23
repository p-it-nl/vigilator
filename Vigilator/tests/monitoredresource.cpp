#include <catch2/catch_all.hpp>
#include <src/monitoredresource.h>
#include <src/exposedresource.h>
#include <src/internalresource.h>
#include <src/onboardresource.h>

TEST_CASE("default exposed resource expecting no name and default config ","[monitoredresource]")
{
    std::string expectedName = "";
    std::string expectedConfigUrl = "";
    bool expectedConfigStatus = false;
    int expectedSize = 0;

    MonitoredResource* resource = new ExposedResource();

    REQUIRE(expectedName == resource->getName());
    REQUIRE(expectedConfigUrl == resource->getConfig()->getEndpoint());
    REQUIRE(expectedConfigStatus == resource->getConfig()->isActive());
    REQUIRE(expectedSize == resource->getParts().size());
}

TEST_CASE("default internal resource expecting no name and default config ","[monitoredresource]")
{
    std::string expectedName = "";
    std::string expectedConfigUrl = "";
    bool expectedConfigStatus = false;
    int expectedSize = 0;

    MonitoredResource* resource = new InternalResource();

    REQUIRE(expectedName == resource->getName());
    REQUIRE(expectedConfigUrl == resource->getConfig()->getEndpoint());
    REQUIRE(expectedConfigStatus == resource->getConfig()->isActive());
    REQUIRE(expectedSize == resource->getParts().size());
}

TEST_CASE("default onboard resource expecting no name and default config ","[monitoredresource]")
{
    std::string expectedName = "";
    std::string expectedConfigUrl = "";
    bool expectedConfigStatus = false;
    int expectedSize = 0;

    MonitoredResource* resource = new OnboardResource();

    REQUIRE(expectedName == resource->getName());
    REQUIRE(expectedConfigUrl == resource->getConfig()->getEndpoint());
    REQUIRE(expectedConfigStatus == resource->getConfig()->isActive());
    REQUIRE(expectedSize == resource->getParts().size());
}

TEST_CASE("exposed resource expecting with emtpy name set and default config ","[monitoredresource]")
{
    std::string expectedName = "";
    std::string expectedConfigUrl = "";
    bool expectedConfigStatus = false;
    int expectedSize = 0;

    MonitoredResource* resource = new ExposedResource();
    resource->setName("");

    REQUIRE(expectedName == resource->getName());
    REQUIRE(expectedConfigUrl == resource->getConfig()->getEndpoint());
    REQUIRE(expectedConfigStatus == resource->getConfig()->isActive());
    REQUIRE(expectedSize == resource->getParts().size());
}

TEST_CASE("exposed resource expecting with name set and default config ","[monitoredresource]")
{
    std::string expectedName = "name";
    std::string expectedConfigUrl = "";
    bool expectedConfigStatus = false;
    int expectedSize = 0;

    MonitoredResource* resource = new ExposedResource();
    resource->setName("name");

    REQUIRE(expectedName == resource->getName());
    REQUIRE(expectedConfigUrl == resource->getConfig()->getEndpoint());
    REQUIRE(expectedConfigStatus == resource->getConfig()->isActive());
    REQUIRE(expectedSize == resource->getParts().size());
}

TEST_CASE("exposed resource decorating without decorator and value","[monitoredresource]")
{
    std::string decorator = "";
    std::string value = "";
    int expectedSize = 0;

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, value);

    REQUIRE(expectedSize == resource->getParts().size());
}

TEST_CASE("exposed resource decorating with decorator and no value","[monitoredresource]")
{
    std::string decorator = "decorator";
    std::string value = "";
    int expectedSize = 1;

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, value);

    REQUIRE(expectedSize == resource->getParts().size());
    REQUIRE(resource->getParts()[decorator]);
}

TEST_CASE("exposed resource decorating with decorator and value","[monitoredresource]")
{
    std::string decorator = "decorator";
    std::string value = "value";
    int expectedSize = 1;
    std::string expectedValue = "value";

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, value);

    REQUIRE(expectedSize == resource->getParts().size());
    MonitoredPart* part = resource->getParts()[decorator];
    REQUIRE(part);
    REQUIRE(expectedValue == part->getItems()[value]);
}

TEST_CASE("exposed resource decorating without decorator, without key and without value","[monitoredresource]")
{
    std::string decorator = "";
    std::string key = "";
    std::string value = "";
    int expectedSize = 0;

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, key, value);

    REQUIRE(expectedSize == resource->getParts().size());
}

TEST_CASE("exposed resource decorating with decorator, without key and without value","[monitoredresource]")
{
    std::string decorator = "decorator";
    std::string key = "";
    std::string value = "";
    int expectedPartsSize = 1;
    int expectedPartItemsSize = 0;

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, key, value);

    REQUIRE(expectedPartsSize == resource->getParts().size());
    MonitoredPart* part = resource->getParts()[decorator];
    REQUIRE(part);
    REQUIRE(expectedPartItemsSize == part->getItems().size());
}

TEST_CASE("exposed resource decorating with decorator, with key and without value","[monitoredresource]")
{
    std::string decorator = "decorator";
    std::string key = "key";
    std::string value = "";
    int expectedPartsSize = 1;
    int expectedPartItemsSize = 1;
    std::string expectedValue = "";

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, key, value);

    REQUIRE(expectedPartsSize == resource->getParts().size());
    MonitoredPart* part = resource->getParts()[decorator];
    REQUIRE(part);
    REQUIRE(expectedPartItemsSize == part->getItems().size());
    REQUIRE(expectedValue == part->getItems()[key]);
}

TEST_CASE("exposed resource decorating with decorator, with key and with value","[monitoredresource]")
{
    std::string decorator = "decorator";
    std::string key = "key";
    std::string value = "value";
    int expectedPartsSize = 1;
    int expectedPartItemsSize = 1;
    std::string expectedValue = "value";

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, key, value);

    REQUIRE(expectedPartsSize == resource->getParts().size());
    MonitoredPart* part = resource->getParts()[decorator];
    REQUIRE(part);
    REQUIRE(expectedPartItemsSize == part->getItems().size());
    REQUIRE(expectedValue == part->getItems()[key]);
}

TEST_CASE("exposed resource decorating with config decorator setting active to true and setting url","[monitoredresource]")
{
    std::string decorator = "Config";
    std::string key = "active";
    std::string value = "true";
    std::string keyUrl = "url";
    std::string valueUrl = "url";
    int expectedPartsSize = 0;
    bool expectedIsActive = true;
    std::string expectedUrl = "url";

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, key, value);
    resource->decorate(decorator, keyUrl, valueUrl);

    REQUIRE(expectedPartsSize == resource->getParts().size());
    Config* config = resource->getConfig();
    REQUIRE(config);
    REQUIRE(expectedIsActive == config->isActive());
    REQUIRE(expectedUrl == config->getEndpoint());
}

TEST_CASE("exposed resource decorating with config decorator setting active to false and setting url","[monitoredresource]")
{
    std::string decorator = "Config";
    std::string key = "active";
    std::string value = "false";
    std::string keyUrl = "url";
    std::string valueUrl = "url";
    int expectedPartsSize = 0;
    bool expectedIsActive = false;
    std::string expectedUrl = "url";

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, key, value);
    resource->decorate(decorator, keyUrl, valueUrl);

    REQUIRE(expectedPartsSize == resource->getParts().size());
    Config* config = resource->getConfig();
    REQUIRE(config);
    REQUIRE(expectedIsActive == config->isActive());
    REQUIRE(expectedUrl == config->getEndpoint());
}

TEST_CASE("exposed resource decorating with decorator and adding two items to decorator","[monitoredresource]")
{
    std::string decorator = "Mock";
    std::string key = "mock";
    std::string value = "mock value";
    std::string secondKey = "second mock";
    std::string secondValue = "second mock value";
    int expectedPartsSize = 1;
    int expectedPartItemsSize =2;
    std::string expectedValue = "mock value";
    std::string expectedSecondValue = "second mock value";
    bool expectedIsActive = false;
    std::string expectedUrl = "";

    MonitoredResource* resource = new ExposedResource();
    resource->decorate(decorator, key, value);
    resource->decorate(decorator, secondKey, secondValue);

    REQUIRE(expectedPartsSize == resource->getParts().size());
    Config* config = resource->getConfig();
    REQUIRE(config);
    REQUIRE(expectedIsActive == config->isActive());
    REQUIRE(expectedUrl == config->getEndpoint());
    MonitoredPart* part = resource->getParts()[decorator];
    std::map<std::string, std::string> items = part->getItems();
    REQUIRE(expectedPartItemsSize == items.size());
    REQUIRE(value == items[key]);
    REQUIRE(secondValue == items[secondKey]);
}
