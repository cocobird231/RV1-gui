cmake_minimum_required(VERSION 3.5)
project(ros_qt_sen)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if($ENV{ROS_DISTRO} STREQUAL "foxy")
  add_compile_options(-DROS_DISTRO=1)
elseif($ENV{ROS_DISTRO} STREQUAL "humble")
  add_compile_options(-DROS_DISTRO=2)
else()# eloquent
  add_compile_options(-DROS_DISTRO=0)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(vehicle_interfaces REQUIRED)
find_package(Qt5  COMPONENTS Charts Core Gui Widgets REQUIRED)

include_directories(
    include
    ${Qt5Widgets_INCLUDE_DIRS}
)

qt5_wrap_cpp(header_SRC
    src/mainwindow.h
    src/form.h
    include/${PROJECT_NAME}/gui_node.h
)
qt5_wrap_ui(UIS_HDRS 
	src/mainwindow.ui
	src/form.ui
)

## Build
add_executable(ros_qt_sen
    src/main.cpp
    src/mainwindow.cpp
    src/gui_node.cpp
    src/form.cpp
    ${header_SRC}
    ${SRC}
    ${UIS_HDRS}
)
ament_target_dependencies(ros_qt_sen rclcpp vehicle_interfaces )

target_link_libraries(ros_qt_sen  Qt5::Charts Qt5::Gui Qt5::Core Qt5::Widgets)

## Install
install(TARGETS
  ros_qt_sen
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
