cmake_minimum_required(VERSION 3.2)
project(TestLibVLCNative)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(PkgConfig REQUIRED)

set(UNIX 1) # Fail if I don't set this
pkg_check_modules(VLC REQUIRED libvlc)

include_directories(${VLC_INCLUDE_DIRS})
link_directories(${VLC_LIBRARY_DIRS})

add_executable(TestLibVLCNative main.cpp)
target_link_libraries(TestLibVLCNative ${VLC_LIBRARIES} Qt5::Widgets)
