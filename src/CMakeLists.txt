cmake_minimum_required(VERSION 3.19)
project(QMultiUnit LANGUAGES CXX)

option(USE_QT5 "Build with Qt 5" OFF)

if(USE_QT5)
    message(STATUS "Building with Qt 5")
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Widgets Network)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
else()
    message(STATUS "Building with Qt 6")
    find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)
    qt_standard_project_setup()
endif()

set(QMULTIUNIT_SOURCES
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    main.cpp
    mainconv.h mainconv.cpp
    rounder.h rounder.cpp
    darkmode.cpp darkmode.h
    additionalconv.h additionalconv.cpp
    currencyapi.h currencyapi.cpp
    images/qmultiunit.icns
)

if(USE_QT5)
    add_executable(QMultiUnit
        WIN32 MACOSX_BUNDLE
        ${QMULTIUNIT_SOURCES}
    )
    if(APPLE)
        set_target_properties(QMultiUnit PROPERTIES
            INSTALL_RPATH "@executable_path/../Frameworks"
        )
    endif()
else()
    qt_add_executable(QMultiUnit
        WIN32 MACOSX_BUNDLE
        ${QMULTIUNIT_SOURCES}
    )
endif()

if(USE_QT5)
    target_sources(QMultiUnit PRIVATE
    resources.qrc)
else()
    qt_add_resources(QMultiUnit "resources"
        PREFIX "/"
        FILES
            images/qmultiunit-1024.png
    )
endif()

set_target_properties(QMultiUnit PROPERTIES
    MACOSX_BUNDLE_ICON_FILE qmultiunit.icns
)

set_source_files_properties(
    images/qmultiunit.icns
    PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
)

if(WIN32)
    target_sources(QMultiUnit PRIVATE
        windows/qmultiunit.rc
    )
endif()

if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE
        windeployqt
        HINTS "${CMAKE_PREFIX_PATH}/bin"
        REQUIRED
    )

    add_custom_command(TARGET QMultiUnit POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            --release
            "$<TARGET_FILE:QMultiUnit>"
        COMMENT "Deploying Qt dependencies..."
    )
endif()

# qt_add_translations(
#     TARGETS QMultiUnit
#     TS_FILES QMultiUnit_en_US.ts
# )

target_link_libraries(QMultiUnit
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

install(TARGETS QMultiUnit
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(USE_QT5)
    message(STATUS "WARNING: Because you are using Qt 5, the automated deployment tools are not available. You will need to deploy the libraries to the application binary manually.")
else()
    qt_generate_deploy_app_script(
        TARGET QMultiUnit
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
endif()
