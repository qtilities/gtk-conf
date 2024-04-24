cmake_minimum_required(VERSION 3.19)
cmake_policy(SET CMP0115 NEW) # explicit files extensions
project(GTKSettings
    VERSION 0.1.0
)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(PROJECT_TRANSLATIONS_UPDATE "Update source translations [default: OFF]" OFF)
set(PROJECT_TRANSLATION_TEST_ENABLED 0 CACHE STRING "Whether to enable translation testing   [default: 0]")
set(PROJECT_TRANSLATION_TEST "it" CACHE STRING      "Country code of language to test in IDE [default: it]")

set(PROJECT_QT_VERSION 6 CACHE STRING "Qt version to use [default: 6]")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(QT NAMES Qt${PROJECT_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED LinguistTools Widgets)
find_package(Qtilitools REQUIRED)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
pkg_search_module(GIO REQUIRED gio-2.0)

set(PROJECT_SOURCES
    src/FontButton.hpp
    src/FontButton.cpp
    src/DialogAbout.hpp
    src/DialogAbout.cpp
    src/DialogAbout.ui
    src/DialogMain.hpp
    src/DialogMain.cpp
    src/DialogMain.ui
    src/Settings.hpp
    src/Settings.cpp
    src/ToolTips.cpp
    src/Utils.hpp
    src/main.cpp
)
set(PROJECT_OTHER_FILES
    .github/workflows/build.yml
    .editorconfig
    .gitattributes
    .gitignore
    README.md
    todo.md
)
source_group("" FILES ${PROJECT_SOURCES})
source_group("" FILES ${PROJECT_OTHER_FILES})

include(Config.cmake)
include(QtAppResources)

set(PROJECT_ALL_FILES
    ${PROJECT_DESKTOP_FILES}
    ${PROJECT_RESOURCES}
    ${PROJECT_SOURCES}
    ${PROJECT_OTHER_FILES}
    ${PROJECT_QM_FILES}
    ${PROJECT_TRANSLATION_SOURCES}
)
qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_ALL_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${GIO_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Threads::Threads
    ${GIO_LIBRARIES}
    ${GLIB_LIBRARIES}
    Qt::Widgets
)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_ID}")

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Woverloaded-virtual
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_NO_KEYWORDS
    APPLICATION_NAME="${PROJECT_ID}"
    APPLICATION_VERSION="${PROJECT_VERSION}"
    PROJECT_APPSTREAM_ID="${PROJECT_APPSTREAM_ID}"
    ORGANIZATION_DOMAIN="${PROJECT_ORGANIZATION_URL}"
    ORGANIZATION_NAME="${PROJECT_ORGANIZATION_NAME}"
    PROJECT_DATA_DIR="${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_ID}"
    PROJECT_DESCRIPTION="${PROJECT_DESCRIPTION}"
    PROJECT_TRANSLATION_TEST="${PROJECT_TRANSLATION_TEST}"
    PROJECT_TRANSLATION_TEST_ENABLED=${PROJECT_TRANSLATION_TEST_ENABLED}
)
install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
message(STATUS "
Project name:                     ${PROJECT_NAME}
Version:                          ${PROJECT_VERSION}
Qt version:                       ${QT_VERSION}
GLib version:                     ${GLIB_VERSION}
Build type:                       ${CMAKE_BUILD_TYPE}
Install prefix:                   ${CMAKE_INSTALL_PREFIX}
Update translations before build: ${PROJECT_TRANSLATIONS_UPDATE}
")
qt_finalize_executable(${PROJECT_NAME})

if (0)
include(DebugUtils)
print_all_variables()
endif()
