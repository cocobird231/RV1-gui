#!/bin/bash

source /opt/ros/foxy/setup.sh
. ./install/setup.sh
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=RelWithDebInfo

