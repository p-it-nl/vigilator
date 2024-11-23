#include <catch2/catch_all.hpp>
#include <src/monitoredresourceconfiguration.h>
#include <filesystem>

TEST_CASE("monitored resource configuration without path, expecting exception","[monitoredresourceconfiguration]")
{
    std::string path = "";
    std::string expectedException = "File with path:  could not be read!";
    int expectedDataSize = 0;

    MonitoredResourceConfiguration monitoredResourceConfiguration = MonitoredResourceConfiguration(path);
    std::string exception;
    try {
        monitoredResourceConfiguration.open();
    } catch(std::string ex) {
        exception = ex;
    }

    std::vector<std::byte> data = monitoredResourceConfiguration.getData();

    REQUIRE(expectedException == exception);
    REQUIRE(expectedDataSize == data.size());
}

TEST_CASE("monitored resource configuration with path, but file does not exist expecting exception","[monitoredresourceconfiguration]")
{
    std::string path = "/mock";
    std::string expectedException = "File with path: /mock could not be read!";
    int expectedDataSize = 0;

    MonitoredResourceConfiguration monitoredResourceConfiguration = MonitoredResourceConfiguration(path);
    std::string exception;
    try {
        monitoredResourceConfiguration.open();
    } catch(std::string ex) {
        exception = ex;
    }

    std::vector<std::byte> data = monitoredResourceConfiguration.getData();

    REQUIRE(expectedException == exception);
    REQUIRE(expectedDataSize == data.size());
}

TEST_CASE("monitored resource configuration with path, expecting to be read","[monitoredresourceconfiguration]")
{
    std::string separator = {std::filesystem::path::preferred_separator};
    std::string path = BINARY_DIR;
    path.append(separator);
    path.append(RESOURCE_FOLDER);
    path.append(separator);
    path.append(CONFIGURATION_FILE);

    MonitoredResourceConfiguration monitoredResourceConfiguration = MonitoredResourceConfiguration(path);

    monitoredResourceConfiguration.open();

    std::vector<std::byte> data = monitoredResourceConfiguration.getData();

    REQUIRE(data.size() > 0);
}


