set(CMAKE_AUTOMOC ON)
set(lib_SRC
    monitoredresource.h
    monitoredresource.cpp
    monitor.h
    monitor.cpp
    resource.h
    exposedresource.h
    exposedresource.cpp
    internalresource.h
    internalresource.cpp
    onboardresource.h
    onboardresource.cpp
    pointintime.h
    pointintime.cpp
    monitoreddata.h
    monitoreddata.cpp
    fileresource.h
    fileresource.cpp
    monitoredresourceconfiguration.h
    monitoredresourceconfiguration.cpp
    monitoredresourcereader.h
    monitoredresourcereader.cpp
    config.h
    config.cpp
    monitoredpart.h
    monitoredpart.cpp
)

add_library(VigilatorCore STATIC ${lib_SRC})
target_link_libraries(VigilatorCore Qt6::Quick)

add_compile_definitions(
    BINARY_DIR="${PROJECT_BINARY_DIR}"
    RESOURCE_FOLDER="Vigilator/resources"
    CONFIGURATION_FILE="monitored-resources.conf"
)

add_executable(core main.cpp)
target_link_libraries(core VigilatorCore)
target_include_directories(VigilatorCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


