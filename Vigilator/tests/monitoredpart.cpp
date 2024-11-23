#include "src/monitoredpart.h"
#include <catch2/catch_all.hpp>

TEST_CASE("default monitoredpart expecting no items and no datetime condition","[monitoredpart]")
{
    std::string expectedDatetimeCondition = "";
    int expectedSize = 0;

    MonitoredPart monitoredPart = MonitoredPart();

    REQUIRE(expectedDatetimeCondition == monitoredPart.getDatetimeCondition());
    REQUIRE(expectedSize == monitoredPart.getItems().size());
}

TEST_CASE("monitoredpart setting item without key and condition","[monitoredpart]")
{
    std::string expectedDatetimeCondition = "";
    int expectedSize = 0;
    std::string key = "";
    std::string value = "";

    MonitoredPart monitoredPart = MonitoredPart();
    monitoredPart.addItem(key, value);

    REQUIRE(expectedDatetimeCondition == monitoredPart.getDatetimeCondition());
    REQUIRE(expectedSize == monitoredPart.getItems().size());
}

TEST_CASE("monitoredpart setting item with key and empty condition","[monitoredpart]")
{
    std::string expectedDatetimeCondition = "";
    int expectedSize = 1;
    std::string key = "key";
    std::string value = "";

    MonitoredPart monitoredPart = MonitoredPart();
    monitoredPart.addItem(key, value);

    REQUIRE(expectedDatetimeCondition == monitoredPart.getDatetimeCondition());
    REQUIRE(expectedSize == monitoredPart.getItems().size());
    REQUIRE(monitoredPart.getItems()[key].empty());
}

TEST_CASE("monitoredpart setting item with key and condition","[monitoredpart]")
{
    std::string expectedDatetimeCondition = "";
    int expectedSize = 1;
    std::string key = "key";
    std::string value = "condition";

    MonitoredPart monitoredPart = MonitoredPart();
    monitoredPart.addItem(key, value);

    REQUIRE(expectedDatetimeCondition == monitoredPart.getDatetimeCondition());
    REQUIRE(expectedSize == monitoredPart.getItems().size());
    REQUIRE(value == monitoredPart.getItems()[key]);
}

TEST_CASE("monitoredpart setting multiple items with key and condition","[monitoredpart]")
{
    std::string expectedDatetimeCondition = "";
    int expectedSize = 3;
    std::string key = "key";
    std::string value = "condition";
    std::string secondKey = "keyTwo";
    std::string secondValue = "condition";
    std::string thirdKey = "keyThree";
    std::string thirdValue = "condition";

    MonitoredPart monitoredPart = MonitoredPart();
    monitoredPart.addItem(key, value);
    monitoredPart.addItem(secondKey, secondValue);
    monitoredPart.addItem(thirdKey, thirdValue);

    REQUIRE(expectedDatetimeCondition == monitoredPart.getDatetimeCondition());
    REQUIRE(expectedSize == monitoredPart.getItems().size());
    std::map<std::string, std::string> items = monitoredPart.getItems();
    REQUIRE(value == items[key]);
    REQUIRE(value == items[secondKey]);
    REQUIRE(value == items[thirdKey]);
}

TEST_CASE("monitoredpart setting item and then updating item","[monitoredpart]")
{
    std::string expectedDatetimeCondition = "";
    int expectedSize = 1;
    std::string key = "key";
    std::string value = "condition";
    std::string secondValue = "second condition";

    MonitoredPart monitoredPart = MonitoredPart();
    monitoredPart.addItem(key, value);
    monitoredPart.addItem(key, secondValue);

    REQUIRE(expectedDatetimeCondition == monitoredPart.getDatetimeCondition());
    REQUIRE(expectedSize == monitoredPart.getItems().size());
    std::map<std::string, std::string> items = monitoredPart.getItems();
    REQUIRE(secondValue == items[key]);
}

TEST_CASE("monitoredpart setting datetime item expecting datetime condition","[monitoredpart]")
{
    std::string expectedDatetimeCondition = "condition";
    int expectedSize = 0;
    std::string key = "datetime";
    std::string value = "condition";

    MonitoredPart monitoredPart = MonitoredPart();
    monitoredPart.addItem(key, value);

    REQUIRE(expectedDatetimeCondition == monitoredPart.getDatetimeCondition());
    REQUIRE(expectedSize == monitoredPart.getItems().size());
}

TEST_CASE("monitoredpart setting datetime item and then updating datetime item","[monitoredpart]")
{
    std::string expectedDatetimeCondition = "condition updated";
    int expectedSize = 0;
    std::string key = "datetime";
    std::string value = "condition";
    std::string secondKey = "datetime";
    std::string secondValue = "condition updated";

    MonitoredPart monitoredPart = MonitoredPart();
    monitoredPart.addItem(key, value);
    monitoredPart.addItem(secondKey, secondValue);

    REQUIRE(expectedDatetimeCondition == monitoredPart.getDatetimeCondition());
    REQUIRE(expectedSize == monitoredPart.getItems().size());
}
