set(CMAKE_AUTOMOC OFF)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

#find_package(Catch2 3 REQUIRED)

add_executable(test
    config.cpp
    monitoredpart.cpp
 #   monitoredresource.cpp
    monitoredresourceconfiguration.cpp
 #   monitoredresourcereader.cpp
    conditionvalidator.cpp
    )

target_link_libraries(test PRIVATE VigilatorCore Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(test)

add_compile_definitions(
    BINARY_DIR="${PROJECT_BINARY_DIR}"
    RESOURCE_FOLDER="Vigilator/resources/test"
    CONFIGURATION_FILE="test-resources.conf"
)
