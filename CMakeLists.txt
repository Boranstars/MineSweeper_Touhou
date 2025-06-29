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

add_executable(MineSweeper_touhou src/main.cpp
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
        src/utils/src/ResourceLoader.cpp
        src/utils/include/ResourceLoader.h
        src/gui/src/windialog.cpp
        src/gui/include/windialog.h
        src/gui/view/WinDialog.ui
)
target_include_directories(MineSweeper_touhou PRIVATE ${CMAKE_SOURCE_DIR}/src/gui/include)
target_include_directories(MineSweeper_touhou PRIVATE ${CMAKE_SOURCE_DIR}/src/core/include)
target_include_directories(MineSweeper_touhou PRIVATE ${CMAKE_SOURCE_DIR}/src/utils/include)
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
