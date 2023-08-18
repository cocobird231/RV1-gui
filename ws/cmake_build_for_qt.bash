#!/bin/bash
source /opt/ros/foxy/setup.sh
. ./install/setup.sh
cd src/ros_qt_sen
cmake . 
make
cd ..
cd ..
