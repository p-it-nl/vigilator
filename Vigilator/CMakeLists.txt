cmake_minimum_required(VERSION 3.16)

project(VigilatorClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Test)
qt_standard_project_setup()

# Define core library
add_library(VigilatorCore STATIC
    resourceitemmodel.h resourceitemmodel.cpp
    notifier.h notifier.cpp
    monitorprocess.h monitorprocess.cpp
    monitorbridge.h monitorbridge.cpp
    resourceslist.h resourceslist.cpp

    src/statusupdater.h src/statusupdater.cpp
    src/resourcestatus.h src/resourcestatus.cpp

    src/monitor/monitoredresource.h src/monitor/monitoredresource.cpp
    src/monitor/monitor.h src/monitor/monitor.cpp
    src/monitor/resource.h
    src/monitor/exposedresource.h src/monitor/exposedresource.cpp
    src/monitor/internalresource.h src/monitor/internalresource.cpp
    src/monitor/onboardresource.h src/monitor/onboardresource.cpp
    src/monitor/monitoreddata.h src/monitor/monitoreddata.cpp
    src/monitor/fileresource.h src/monitor/fileresource.cpp
    src/monitor/monitoredresourceconfiguration.h src/monitor/monitoredresourceconfiguration.cpp
    src/monitor/monitoredresourcereader.h src/monitor/monitoredresourcereader.cpp
    src/monitor/config.h src/monitor/config.cpp
    src/monitor/monitoredpart.h src/monitor/monitoredpart.cpp
    src/monitor/conditionvalidator.h src/monitor/conditionvalidator.cpp
)
target_include_directories(VigilatorCore
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# Link libraries to VigilatorCore
target_link_libraries(VigilatorCore
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

# Define executable for VigilatorClient
qt_add_executable(VigilatorClient
    main.cpp
    MANUAL_FINALIZATION
    ${app_icon_resource_windows}
)

# Link libraries to VigilatorClient
target_link_libraries(VigilatorClient
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::Qml
    Qt6::Test
    VigilatorCore
)

# Define the test executable
add_executable(Test
    test/resourceitemmodeltest.cpp
    test/resourceitemmodeltest.h
    test/conditionvalidatortest.h
    test/conditionvalidatortest.cpp
    test/testclass.h
    test/testclass.cpp
    test/main.cpp
)

target_include_directories(Test
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link the test executable with Qt and the core library
target_link_libraries(Test
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Test
    Qt6::Qml
    VigilatorCore
)

# Enable testing
enable_testing()

# Add the test to CTest (CMake's testing framework)
add_test(NAME ResourceItemModelTest COMMAND ResourceItemModelTest)
add_test(NAME ConditionValidatorTest COMMAND ConditionValidatorTest)

# Add Android OpenSSL support if necessary
if (ANDROID)
    Include(FetchContent)
    FetchContent_Declare(
        android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL      https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)
endif()

# Set up the app icon for Windows if necessary
set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.rc")

# Add Android specific configurations
if (ANDROID)
    add_android_openssl_libraries(VigilatorClient)
endif()
set_property(TARGET VigilatorClient APPEND PROPERTY
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

# Add QML module for the client application
qt_add_qml_module(VigilatorClient
    URI Vigilator
    VERSION 1.0
    QML_FILES
        Main.qml
        ResourcesList.qml
    RESOURCES
        resources/logo.svg
        resources/logo-name.svg
        resources/ok.svg
        resources/warning.svg
        resources/error.svg
        resources/logo.ico
        resources/icon.rc
        resources/monitored-resources.conf
        resources/test/test-resources.conf
        android/src/nl/p_it/vigilator/MonitorService.java
        android/src/nl/p_it/vigilator/NotificationClient.java
        android/src/nl/p_it/vigilator/HealthTester.java
        android/src/nl/p_it/vigilator/HealthTesterService.java
        android/AndroidManifest.xml
)

# Set the bundle properties for macOS or iOS if needed
set_target_properties(VigilatorClient PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER nl.p_it.vigilator
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Add support for QuickTemplates2 if cross-compiling on Linux
if(UNIX AND NOT APPLE AND CMAKE_CROSSCOMPILING)
    find_package(Qt6 REQUIRED COMPONENTS QuickTemplates2)
    target_link_libraries(VigilatorClient PRIVATE Qt6::QuickTemplates2)
endif()

# Install settings
include(GNUInstallDirs)
install(TARGETS VigilatorClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Define compile definitions
add_compile_definitions(
    CONFIGURATION_FILE="monitored-resources.conf"
    BINARY_DIR="${PROJECT_BINARY_DIR}"
    RESOURCE_FOLDER="Vigilator/resources"
    ANDROID_ASSETS="assets:"
)

if (NOT ANDROID)
    add_compile_definitions(
        IS_ANDROID=0
    )
endif()

if (ANDROID)
    add_compile_definitions(
        IS_ANDROID=1
    )
endif()


