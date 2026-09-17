cmake_minimum_required(VERSION 3.19)
project(QMultiUnit LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools Network)

qt_standard_project_setup()

qt_add_executable(QMultiUnit
    WIN32 MACOSX_BUNDLE
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

qt_add_resources(QMultiUnit "resources"
    PREFIX "/"
    FILES
        images/qmultiunit-1024.png
)

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

qt_generate_deploy_app_script(
    TARGET QMultiUnit
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
