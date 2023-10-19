#ver=1.3
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

import os
import yaml
from yaml import load, Loader

def generate_launch_description():
    commonFilePath = os.path.join(get_package_share_directory('cpp_gui'), 'launch/common.yaml')
    with open(commonFilePath, 'r') as f:
        data = yaml.load(f, Loader=Loader)
    return LaunchDescription([
        Node(
            package="cpp_gui",
            namespace=data['generic_prop']['namespace'],
            executable="ros2_gui",
            output="screen",
            emulate_tty=True,
            parameters=[
                {
                }
            ]
        )
    ])
