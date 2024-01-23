cmake_minimum_required(VERSION 3.5)
project(cpp_gui)

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
find_package(Qt5  COMPONENTS Charts Core Gui Widgets Network Svg REQUIRED)
find_package(libssh REQUIRED)
find_package(OpenCV ${VERSION_REQ_OCV} REQUIRED)
include_directories(
    include
    ${Qt5Widgets_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)
link_directories(${OpenCV_LIBRARY_DIRS})
qt5_wrap_cpp(header_SRC
    src/mainwindow.h

    src/qos_device_dialog/qosdevicedialog.h
    src/sensor_form/sensor_form.h
    src/data_server_record/data_server_record.h

    src/install_shell/install_shell.h
    src/install_shell/install_option/install_option.h
    src/install_shell/install_device_infor/install_device_infor.h
    src/install_shell/install_process/install_process.h
    src/install_shell/install_common/install_common.h
    src/image_display/image_form.h

    src/safety/safety.h

    include/node/gui_node.h
)
qt5_wrap_ui(UIS_HDRS 
	src/mainwindow.ui
  src/qos_device_dialog/qosdevicedialog.ui
  src/data_server_record/data_server_record.ui
  src/image_display/image_form.ui

	src/sensor_form/sensor_form.ui
  src/install_shell/install_shell.ui
  src/install_shell/install_option/install_option.ui
  src/install_shell/install_device_infor/install_device_infor.ui
  src/install_shell/install_process/install_process.ui
  src/install_shell/install_common/install_common.ui
  src/safety/safety.ui


)

## Build
add_executable(ros2_gui
    src/main.cpp
    src/qos_device_dialog/qosdevicedialog.cpp
    src/data_server_record/data_server_record.cpp
    src/image_display/image_form.cpp
    src/install_shell/install_shell.cpp
    src/install_shell/install_option/install_option.cpp
    src/install_shell/install_device_infor/install_device_infor.cpp
    src/install_shell/install_process/install_process.cpp

    src/install_shell/install_common/install_common.cpp

    src/mainwindow.cpp
    src/node/gui_node.cpp
    src/sensor_form/sensor_form.cpp
    src/safety/safety.cpp

    ${header_SRC}
    ${SRC}
    ${UIS_HDRS}
    
)

ament_target_dependencies(ros2_gui rclcpp vehicle_interfaces )

target_link_libraries(ros2_gui  Qt5::Charts Qt5::Gui Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg ssh -lstdc++fs ${OpenCV_LIBRARIES})

## Install
install(TARGETS
  ros2_gui
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
