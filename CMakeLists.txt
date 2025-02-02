cmake_minimum_required(VERSION 3.20)

include(FetchContent)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

# Add project_options from https://github.com/aminya/project_options
# Change the version in the following URL to update the package (watch the releases of the repository for future updates)
set(PROJECT_OPTIONS_VERSION "v0.41.0")
FetchContent_Declare(
        _project_options
        URL https://github.com/aminya/project_options/archive/refs/tags/${PROJECT_OPTIONS_VERSION}.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

run_conan(
        HOST_PROFILE default auto-cmake
        BUILD_PROFILE default
        INSTALL_ARGS --build=missing
)

project(kflash VERSION 0.0.1 DESCRIPTION "Application to study using flashcards" LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.8.2/lib/cmake") # Change to your QT directory
find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets)


set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")

project_options(
        PREFIX "kflash"
        ENABLE_CACHE
        ${ENABLE_CPPCHECK}
#        ${ENABLE_CLANG_TIDY}
        WARNINGS_AS_ERRORS
        CPPCHECK_OPTIONS --library=qt
)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/MainWindow.cpp
        include/MainWindow.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}
        PRIVATE kflash_project_options kflash_project_warnings
)

target_find_dependencies(${PROJECT_NAME}
        PRIVATE_CONFIG
        fmt
        spdlog
)

target_link_system_libraries(${PROJECT_NAME}
        PRIVATE
        fmt::fmt
        spdlog::spdlog
        Qt6::Widgets
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "Testing enabled")
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif ()

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()