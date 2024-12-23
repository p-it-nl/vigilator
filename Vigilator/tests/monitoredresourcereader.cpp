#include <catch2/catch_all.hpp>
#include <src/monitoredresourcereader.h>

TEST_CASE("process without monitored resource configuration, expecting exception","[monitoredresourcereader]")
{
    MonitoredResourceConfiguration* monitoredResourceConfiguration = NULL;
    std::string expectedException = "File with path:  could not be read!";
    int expectedDataSize = 0;

    MonitoredResourceReader monitoredresourcereader = MonitoredResourceReader();
    std::string exception;
    try {
        monitoredresourcereader.process(monitoredResourceConfiguration);
    } catch(std::string ex) {
        exception = ex;
    }

   // monitoredresourcereader.getResources()

    REQUIRE(expectedException == exception);
   // REQUIRE(expectedDataSize == data.size());
}

/*
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
*/
