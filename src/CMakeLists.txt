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
)

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
