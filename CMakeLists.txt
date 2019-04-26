cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(QGraphicsView_bounding_box_bug_solution)

add_compile_options(-std=c++11)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
include_directories(src)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(custom_view SHARED src/customview.cpp src/customview.h)
target_link_libraries(custom_view Qt5::Core Qt5::Widgets)

add_library(customgraphicspixmapitem SHARED src/customgraphicspixmapitem.cpp src/customgraphicspixmapitem.h)
target_link_libraries(customgraphicspixmapitem Qt5::Core Qt5::Widgets)

add_library(image_control SHARED src/imagecontrol.cpp src/imagecontrol.h src/imagecontrol.ui)
target_link_libraries(image_control Qt5::Core Qt5::Widgets custom_view customgraphicspixmapitem)

add_library(mainwindow SHARED src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui)
target_link_libraries(mainwindow Qt5::Core Qt5::Widgets image_control)

add_executable(main_test src/main.cpp)
target_link_libraries(main_test  Qt5::Core Qt5::Widgets mainwindow)
