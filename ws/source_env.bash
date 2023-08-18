#!/bin/bash

source /opt/ros/foxy/setup.sh
. ./install/setup.sh
colcon buid
ros2 run ros_qt_sen ros_qt_sen
