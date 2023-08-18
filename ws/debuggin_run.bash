#!/bin/bash
source /opt/ros/foxy/setup.sh
. ./install/setup.sh

ros2 run --prefix 'gdbserver localhost:3000' ros_qt_sen ros_qt_sen
