cmake_minimum_required(VERSION 3.16)

project(VigilatorClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
qt_standard_project_setup(REQUIRES 6.5)

if (ANDROID)
    Include(FetchContent)
    FetchContent_Declare(
      android_openssl
      DOWNLOAD_EXTRACT_TIMESTAMP true
      URL      https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
#      URL_HASH MD5=c97d6ad774fab16be63b0ab40f78d945 #optional
    )
    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)
endif()
# instead of downloading it a milion times maybe better to reference local
# include(<path/to/android_openssl>/android_openssl.cmake)
# @see https://github.com/KDAB/android_openssl

#add_subdirectory(src)
add_subdirectory(tests)

qt_standard_project_setup()

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.rc")

qt_add_executable(VigilatorClient
    main.cpp
    MANUAL_FINALIZATION
    ${app_icon_resource_windows}
)
if (ANDROID)
    add_android_openssl_libraries(VigilatorClient)
endif()
set_property(TARGET VigilatorClient APPEND PROPERTY
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

qt_add_qml_module(VigilatorClient
    URI Vigilator
    VERSION 1.0
    QML_FILES
        main.qml
        ResourcesList.qml
    RESOURCES
        resources/logo.svg
        resources/logo-name.svg
        resources/logo.ico
        resources/icon.rc
        resources/monitored-resources.conf
        resources/test/test-resources.conf
        android/src/nl/p_it/vigilator/MonitorService.java
        android/src/nl/p_it/vigilator/NotificationClient.java
        android/src/nl/p_it/vigilator/HealthTester.java
        android/src/nl/p_it/vigilator/HealthTesterService.java
        android/AndroidManifest.xml
    SOURCES
        resourceitemmodel.h resourceitemmodel.cpp
        notifier.h notifier.cpp
        monitorprocess.h monitorprocess.cpp
        monitorbridge.h monitorbridge.cpp
        resourceslist.h resourceslist.cpp

        src/monitoredresource.h src/monitoredresource.cpp
        src/monitor.h src/monitor.cpp
        src/resource.h
        src/exposedresource.h src/exposedresource.cpp
        src/internalresource.h src/internalresource.cpp
        src/onboardresource.h src/onboardresource.cpp
        src/monitoreddata.h src/monitoreddata.cpp
        src/fileresource.h src/fileresource.cpp
        src/monitoredresourceconfiguration.h src/monitoredresourceconfiguration.cpp
        src/monitoredresourcereader.h src/monitoredresourcereader.cpp
        src/config.h src/config.cpp
        src/monitoredpart.h src/monitoredpart.cpp
        src/conditionvalidator.h src/conditionvalidator.cpp
)

qt_finalize_executable(VigilatorClient)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(VigilatorClient PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER nl.p_it.vigilator
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(VigilatorClient
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::Qml
)

if(UNIX AND NOT APPLE AND CMAKE_CROSSCOMPILING)
    find_package(Qt6 REQUIRED COMPONENTS QuickTemplates2)
    target_link_libraries(VigilatorClient PRIVATE Qt6::QuickTemplates2)
endif()

include(GNUInstallDirs)
install(TARGETS VigilatorClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

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


# To test
set(lib_SRC
    src/monitoredresource.h src/monitoredresource.cpp
    src/exposedresource.h src/exposedresource.cpp
    src/monitoreddata.h src/monitoreddata.cpp
    src/monitoredresource.h src/monitoredresource.cpp
    src/monitoredresourceconfiguration.h src/monitoredresourceconfiguration.cpp
    src/monitoredresourcereader.h src/monitoredresourcereader.cpp
    src/config.h src/config.cpp
    src/monitoredpart.h src/monitoredpart.cpp
    src/conditionvalidator.h src/conditionvalidator.cpp
    src/fileresource.h src/fileresource.cpp
)

add_library(VigilatorCore STATIC ${lib_SRC})
target_link_libraries(VigilatorCore Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::Qml)
target_include_directories(VigilatorCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


