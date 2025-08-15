cmake_minimum_required(VERSION 3.31)
project(MineSweeper_touhou)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/gui/view)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets

        REQUIRED)
set(CORE_DIR ${CMAKE_SOURCE_DIR}/src/core)
set(CORE_INCLUDE_DIR ${CORE_DIR}/include)
set(CORE_SOURCES_DIR ${CORE_DIR}/src)

set(UTILS_DIR ${CMAKE_SOURCE_DIR}/src/utils)
set(UTILS_INCLUDE_DIR ${UTILS_DIR}/include)
set(UTILS_SOURCES_DIR ${UTILS_DIR}/src)



add_executable(MineSweeper_touhou
        src/main.cpp
        src/gui/src/mainwindow.cpp
        src/gui/include/mainwindow.h
        src/gui/view/MainWindow.ui
        src/gui/src/customdialog.cpp
        src/gui/include/customdialog.h
        src/gui/view/CustomDialog.ui
        src/gui/src/scenewidget.cpp
        src/gui/include/scenewidget.h
        src/core/src/mineunit.cpp
        src/core/include/mineunit.h
        src/utils/include/constants.h
        src/core/src/gameboard.cpp
        src/core/include/gameboard.h
        resources/resources.qrc
        src/utils/src/resourceloader.cpp
        src/utils/include/resourceloader.h
        src/gui/src/windialog.cpp
        src/gui/include/windialog.h
        src/gui/view/WinDialog.ui
        src/gui/src/lostdialog.cpp
        src/gui/include/lostdialog.h
        src/gui/view/LostDialog.ui
)
target_include_directories(MineSweeper_touhou PRIVATE ${CMAKE_SOURCE_DIR}/src/gui/include)
target_include_directories(MineSweeper_touhou PRIVATE ${CORE_INCLUDE_DIR})
target_include_directories(MineSweeper_touhou PRIVATE ${UTILS_INCLUDE_DIR})
target_link_libraries(MineSweeper_touhou
        Qt::Core
        Qt::Gui
        Qt::Widgets


)

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

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)

